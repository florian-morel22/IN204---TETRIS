#include "block.hpp"
#include "player.hpp"
#include "utils.hpp"
#include <iostream>
#include <thread>
#include <vector>

namespace tetris {

class Network {

private:
  unsigned short port;
  sf::IpAddress ip;
  bool HostIsRunning;

  /* For clients */
  sf::TcpSocket socketAsClient;

  /* For Host */
  sf::TcpListener listener;
  sf::SocketSelector selector;

  std::vector<sf::TcpSocket *> socketsAsHost;
  std::vector<Player *> all_players;

  std::thread hostT;
  void Host();

public:
  Network();
  // TODO : ~Network()
  void runHost();

  void connectAsClient(sf::IpAddress ip, short int port, Player &player);
  std::string getDataFromHost(Player &, std::vector<Player *> &);
  void sendScoreToHost(Player &);

  sf::IpAddress get_ip() const { return ip; }
  unsigned short get_port() const { return port; }
  void set_port(unsigned short new_port) { port = new_port; }

  void stop_Host();
};

}; // namespace tetris
