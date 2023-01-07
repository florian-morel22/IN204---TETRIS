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

  sf::TcpListener listener;
  sf::SocketSelector selector;

  bool HostIsRunning;
  std::thread hostT;
  void Host();

  std::vector<sf::TcpSocket *> socketsAsHost;
  sf::TcpSocket socketAsClient;

public:
  Network();
  void runHost();

  void connectAsClient(sf::IpAddress ip, short int port, Player &player);
  void getInfosFromOtherPlayers(Player &);
  void sendInfosToHost(Player &);

  sf::IpAddress get_ip() const { return ip; }
  unsigned short get_port() const { return port; }
  void set_port(unsigned short new_port) { port = new_port; }

  void stop_Host();
};

}; // namespace tetris
