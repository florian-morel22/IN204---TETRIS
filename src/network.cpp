#include "network.hpp"

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <string>

namespace tetris {

struct Data {
  std::string message;
  std::string pseudo;
  int score;
};

sf::Packet &operator<<(sf::Packet &packet, const Data &data) {
  return packet << data.message << data.pseudo << data.score;
}

sf::Packet &operator>>(sf::Packet &packet, Data &data) {
  return packet >> data.message >> data.pseudo >> data.score;
}

Network::Network() {
  port = 3500;
  ip = "147.250.226.160";
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

          Data data;
          std::string pseudo_;

          /* Host display : pseudo is connected */
          receivePacket >> pseudo_;
          std::cout << pseudo_ << " is connected. " << std::endl;

          /* The new player receives the data of all others players */

          std::cout << "size all players : " << all_players.size() << std::endl;
          data.message = "add player to other_players";
          for (Player *p : all_players) {
            data.pseudo = p->get_pseudo();
            std::cout << "pseudo : " << data.pseudo << std::endl;
            sf::Packet sendPacket;
            sendPacket << data;
            socketsAsHost[socketsAsHost.size() - 1]->send(sendPacket);
          }

          /* The new player is added on the host */
          Player *new_player = new Player(pseudo_);
          all_players.push_back(new_player);

          /* All other players receive data of this new player */
          sf::Packet sendPacket;
          data.message = "add player to other_players";
          data.pseudo = pseudo_;
          sendPacket << data;

          std::cout << "pseudo to send : " << pseudo_ << std::endl;

          for (size_t j = 0; j < socketsAsHost.size() - 1; j++) {
            socketsAsHost[j]->send(sendPacket);
          }
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
              // To Test : sendPacket = receivePacket

              for (size_t j = 0; j < socketsAsHost.size(); j++) {
                if (j != i) {
                  socketsAsHost[j]->send(sendPacket);
                }
              }

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

  std::cout << "ip : " << ip << ", port : " << port << std::endl;
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

std::string Network::getDataFromHost(Player &player,
                                     std::vector<Player *> &other_players) {
  sf::Packet receivePacket;
  Data data;

  if (socketAsClient.receive(receivePacket) == sf::Socket::Done) {
    receivePacket >> data;

    if (data.message == "update scores") {
      std::cout << "Joueur : " << data.pseudo << " a le score : " << data.score
                << std::endl;

      // Change the score of the concerning player in other_players
      auto it = std::find_if(
          other_players.begin(), other_players.end(),
          [data](Player *p) { return p->get_pseudo() == data.pseudo; });
      int ind = std::distance(other_players.begin(), it);
      other_players[ind]->set_score(data.score);

      for (Player *p : other_players) {
        std::cout << "Player : " << p->get_pseudo()
                  << ", Score : " << std::to_string(p->get_score())
                  << std::endl;
      }
      return data.message;
    }

    else if (data.message == "Serveur coupé") {
      std::cout << data.message << std::endl;
      player.set_Client(false);
      other_players.clear();
    }

    else if (data.message == "add player to other_players") {
      Player *newPlayer = new Player(data.pseudo);
      other_players.push_back(newPlayer);
      std::cout << "Player " << data.pseudo << " ajouté à other_players"
                << std::endl;
    }
  }
  return data.message;
}

void Network::sendScoreToHost(Player &player) {
  sf::Packet sendPacket;
  Data data;

  data.message = "update scores";
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

  data.message = "Serveur coupé";
  sendPacket << data;

  socketAsClient.send(sendPacket);
}

} // namespace tetris