#include <string>

namespace tetris {

class Player {
private:
  std::string pseudo_;
  int score_;

public:
  auto get_pseudo() const -> std::string;
  auto set_pseudo(std::string) -> void;
  auto get_score() const -> int;
  auto set_score(int) -> void;
};

} // namespace tetris