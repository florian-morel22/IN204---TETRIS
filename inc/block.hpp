#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "grid.hpp"
#include "utils.hpp"

namespace tetris {

class Block {

protected:
  int value;
  int rotate_value = 0;
  std::vector<sf::Vector2i> list_squares;

public:
  auto get_pos() const -> sf::Vector2i;
  auto get_value() const -> int;
  auto get_list_squares() const -> std::vector<sf::Vector2i>;
  auto display_block(Grid &) -> void;
  auto hide_block(Grid &) -> void;
  auto go_down(Grid &) -> bool;
  auto go_right(Grid &) -> void;
  auto go_left(Grid &) -> void;

  virtual void rotate(Grid &) = 0;
};

} // namespace tetris

#endif // !BLOCK_HPP