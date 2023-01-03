#include "block.hpp"
#include "utils.hpp"
#include <vector>

namespace tetris {

class Network {
private:
  std::vector<sf::IpAddress> list_clients;
  std::vector<unsigned short> list_ports;

public:
  auto send_scores_to_other_players(int score) const -> void;
  auto receive_scores_from_other_players() -> std::vector<int>;

  auto send_blocks_to_other_players(std::vector<int>) const -> void;
  auto receive_blocks_from_other_players() -> std::vector<int>;
};

}; // namespace tetris