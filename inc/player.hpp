#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

namespace tetris {

class Player {
private:
  std::string pseudo_;
  int score_;
  int level_;

  bool Host_;
  bool Client_;

  int numBlock;

public:
  Player();
  Player(std::string);

  auto get_pseudo() const -> std::string;
  auto set_pseudo(std::string) -> void;

  auto get_score() const -> int;
  auto add_score(int) -> void;
  auto set_score(int) -> void;

  auto reset_level() -> void;
  auto set_level(int) -> void;
  auto get_level() const -> int;

  auto isHost() const -> bool;
  auto set_Host(bool) -> void;

  auto isClient() const -> bool;
  auto set_Client(bool) -> void;

  auto get_numBlock() const -> int;
  auto add_numBlock() -> void;
  auto reset_numBlock() -> void;
};

} // namespace tetris

#endif // !GAME_HPP