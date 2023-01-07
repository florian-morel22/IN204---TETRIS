#include "network.hpp"

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <string>

namespace tetris {

struct Data {
  int type;
  std::string pseudo;
  int score;
  std::string message;
};

sf::Packet &operator<<(sf::Packet &packet, const Data &data) {
  return packet << data.type << data.pseudo << data.score << data.message;
}

sf::Packet &operator>>(sf::Packet &packet, Data &data) {
  return packet >> data.type >> data.pseudo >> data.score >> data.message;
}

Network::Network() {
  port = 3500;
  ip = sf::IpAddress::getLocalAddress();
}

void Network::runHost() {
  hostT = std::thread(&Network::Host, this);
  hostT.detach();
}

void Network::Host() {

  HostIsRunning = true;

  listener.listen(port);
  selector.add(listener);

  if (listener.listen(port) == sf::Socket::Done) {
    std::cout << "Serveur correctement lancé" << std::endl;
  } else {
    exit(0);
  }

  while (HostIsRunning) {

    if (selector.wait()) {
      /*Si le selecteur est prêt a écouter le listener, il l'ecoute.
       *On li cette partie du code lorsque que qqch a été envoyé par un client
       *mais on ne le connait pas.
       */
      if (selector.isReady(listener)) {
        sf::TcpSocket *socket = new sf::TcpSocket();
        listener.accept(*socket);
        selector.add(*socket);
        socketsAsHost.push_back(socket);

        sf::Packet receivePacket;
        if (socket->receive(receivePacket) == sf::Socket::Done) {
          std::string pseudo_;
          receivePacket >> pseudo_;
          std::cout << pseudo_ << " vient de se connecter. " << std::endl;
        }
      } else {
        for (size_t i = 0; i < socketsAsHost.size(); i++) {
          if (selector.isReady(*socketsAsHost[i])) {
            sf::Packet receivePacket;
            sf::Packet sendPacket;
            Data data;

            if (socketsAsHost[i]->receive(receivePacket) == sf::Socket::Done) {

              receivePacket >> data;

              sendPacket << data;

              for (size_t j = 0; j < socketsAsHost.size(); j++) {
                if (j != i) {
                  socketsAsHost[j]->send(sendPacket);
                }
              }

              if (data.type == 2)
                if (data.message == "Serveur coupé") {
                  HostIsRunning = false;
                  socketsAsHost.clear();
                }
            }
          }
        }
      }
    }
  }
}

void Network::connectAsClient(sf::IpAddress ip, short int port,
                              Player &player) {

  if (socketAsClient.connect(ip, port) == sf::Socket::Done) {
    socketAsClient.setBlocking(false);
    std::cout << "Connecté au serveur." << std::endl;

    sf::Packet sendPacket;
    sendPacket << player.get_pseudo();
    socketAsClient.send(sendPacket);

    player.set_Client(true);
  } else {
    std::cout << "Serveur down." << std::endl;
  }
}

void Network::getInfosFromOtherPlayers(Player &player) {
  sf::Packet receivePacket;
  Data data;

  if (socketAsClient.receive(receivePacket) == sf::Socket::Done) {
    receivePacket >> data;

    if (data.type == 1) {
      std::cout << "Joueur : " << data.pseudo << " a le score : " << data.score
                << std::endl;
    } else if (data.type == 2) {
      std::cout << data.message << std::endl;
      if (data.message == "Serveur coupé")
        player.set_Client(false);
    }
  }
}

void Network::sendInfosToHost(Player &player) {
  sf::Packet sendPacket;
  Data data;
  data.type = 1;
  data.pseudo = player.get_pseudo();
  data.score = player.get_score();
  sendPacket << data;
  socketAsClient.send(sendPacket);
}

void Network::stop_Host() {

  printf("Serveur arreté.\n");

  // Prévenir chaque client que le serveur est coupé.
  sf::Packet sendPacket;
  Data data;

  data.type = 2;
  data.message = "Serveur coupé";
  sendPacket << data;

  socketAsClient.send(sendPacket);
}

} // namespace tetris