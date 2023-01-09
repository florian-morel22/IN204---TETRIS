#include <string>
#include <vector>

namespace tetris {

class Player {
private:
  std::string pseudo_;
  int score_;

  bool Host_;
  bool Client_;

public:
  Player();
  Player(std::string);

  auto get_pseudo() const -> std::string;
  auto set_pseudo(std::string) -> void;

  auto get_score() const -> int;
  auto add_score(int) -> void;
  auto set_score(int) -> void;

  auto isHost() const -> bool;
  auto set_Host(bool) -> void;

  auto isClient() const -> bool;
  auto set_Client(bool) -> void;
};

} // namespace tetris