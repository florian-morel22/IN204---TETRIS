#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "./types_block/block_I.hpp"
#include "./types_block/block_J.hpp"
#include "./types_block/block_L.hpp"
#include "./types_block/block_O.hpp"
#include "./types_block/block_S.hpp"
#include "./types_block/block_T.hpp"
#include "./types_block/block_Z.hpp"
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

  int numBlock;

  std::vector<sf::TcpSocket *> socketsAsHost;
  std::vector<Player *> all_players;

  std::thread hostT;
  void Host();

  void generate_new_Block();
  void add_new_Block_to_listBlocks(int, int);

public:
  std::map<int, Block *> listBlocks;

  Network();
  ~Network();
  void runHost();

  bool connectAsClient(sf::IpAddress ip, short int port, Player &player);
  std::string getDataFromHost(Player &, std::vector<Player *> &);
  void sendDataToHost(Player &, std::string);

  sf::IpAddress get_ip() const { return ip; }
  unsigned short get_port() const { return port; }
  void set_port(unsigned short new_port) { port = new_port; }

  void reset_IP_port();

  void stop_Host();
};

}; // namespace tetris

#endif // !NETWORK_HPP
