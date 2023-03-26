#include "../inc/network.hpp"

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <string>

namespace tetris {

struct Data {
  std::string message;
  std::string pseudo;
  int score;
  int num_block;
  int type_block; // between 1 and 7
};

sf::Packet &operator<<(sf::Packet &packet, const Data &data) {
  return packet << data.message << data.pseudo << data.score << data.num_block
                << data.type_block;
}

sf::Packet &operator>>(sf::Packet &packet, Data &data) {
  return packet >> data.message >> data.pseudo >> data.score >>
         data.num_block >> data.type_block;
}

Network::Network() {

  // initialization to use random numbers
  std::srand((unsigned int)time(nullptr));

  port = 3001 + (std::rand() % 1000);
  ip = sf::IpAddress::getLocalAddress();
  numBlock = 0;
}

Network::~Network() {}

void Network::reset_IP_port() {
  ip = sf::IpAddress::getLocalAddress();
  int old_port = port;
  while (old_port == port) {
    port = 3001 + (std::rand() % 1000);
  }
};

void Network::add_new_Block_to_listBlocks(int num, int block) {
  enum b { I = 1, J, L, O, S, Z, T };

  Block *newBlock;

  switch (block) {
  case I:
    newBlock = new Block_I(5, 3);
    break;
  case J:
    newBlock = new Block_J(6, 3);
    break;
  case L:
    newBlock = new Block_L(6, 3);
    break;
  case O:
    newBlock = new Block_O(6, 2);
    break;
  case S:
    newBlock = new Block_S(5, 2);
    break;
  case Z:
    newBlock = new Block_Z(5, 2);
    break;
  default:
    newBlock = new Block_T(6, 3);
  }
  listBlocks.insert({num, newBlock});
}

void Network::runHost() {
  hostT = std::thread(&Network::Host, this);
  hostT.detach();
}

void Network::Host() {

  HostIsRunning = true;

  listener.listen(port);
  selector.add(listener);

  if (listener.listen(port) != sf::Socket::Done) {
    exit(0);
  }

  while (HostIsRunning) {
    if (selector.wait()) {
      /*Si le selecteur est prêt a écouter le listener, il l'ecoute.
       *On lit cette partie du code lorsque que qqch a été envoyé par un client
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

          /* The new player receives the data of all others players */

          data.message = "add player to other_players";
          for (Player *p : all_players) {
            sf::Packet sendPacket;

            data.pseudo = p->get_pseudo();

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

              if (data.message == "generate new block") {
                data.num_block = numBlock;
                data.type_block = 1 + (std::rand() % 8);

                numBlock += 1;
              }

              sendPacket << data;

              if (data.message == "generate new block" ||
                  data.message == "play") {
                for (size_t j = 0; j < socketsAsHost.size(); j++) {
                  socketsAsHost[j]->send(sendPacket);
                }
              } else {
                for (size_t j = 0; j < socketsAsHost.size(); j++) {
                  if (j != i) {
                    socketsAsHost[j]->send(sendPacket);
                  }
                }
              }

              if (data.message == "server down") {
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

bool Network::connectAsClient(sf::IpAddress ip, short int port,
                              Player &player) {

  if (socketAsClient.connect(ip, port) == sf::Socket::Done) {
    socketAsClient.setBlocking(false);

    sf::Packet sendPacket;
    sendPacket << player.get_pseudo();
    socketAsClient.send(sendPacket);

    player.set_Client(true);

    return true;
  } else {
    return false;
  }
}

std::string Network::getDataFromHost(Player &player,
                                     std::vector<Player *> &other_players) {
  sf::Packet receivePacket;
  Data data;

  if (socketAsClient.receive(receivePacket) == sf::Socket::Done) {
    receivePacket >> data;

    if (data.message == "update scores") {

      // Change the score of the concerning player in other_players
      auto it = std::find_if(
          other_players.begin(), other_players.end(),
          [data](Player *p) { return p->get_pseudo() == data.pseudo; });
      int ind = std::distance(other_players.begin(), it);
      other_players[ind]->set_score(data.score);

      return data.message;
    }

    else if (data.message == "server down") {
      std::cout << data.message << std::endl;
      player.set_Client(false);
      other_players.clear();
    }

    else if (data.message == "add player to other_players") {
      Player *newPlayer = new Player(data.pseudo);
      other_players.push_back(newPlayer);
    }

    else if (data.message == "generate new block") {
      printf("data.num_block : %d, data.type_block : %d\n", data.num_block,
             data.type_block);
      add_new_Block_to_listBlocks(data.num_block, data.type_block);
    }
  }
  return data.message;
}

void Network::sendDataToHost(Player &player, std::string message) {
  sf::Packet sendPacket;
  Data data;

  if (message == "update scores") {
    data.pseudo = player.get_pseudo();
    data.score = player.get_score();
  }

  data.message = message;
  sendPacket << data;

  socketAsClient.send(sendPacket);
}

} // namespace tetris