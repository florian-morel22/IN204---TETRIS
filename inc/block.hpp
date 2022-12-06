#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <iostream>
#include <map>

#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>

#include "grid.hpp"
#include "utils.hpp"

class Block {
protected:
  unsigned int value;
  unsigned int rotate_value = 0;
  std::vector<sf::Vector2u> list_squares;

public:
  sf::Vector2u get_pos() const;
  unsigned int get_value() const;
  std::vector<sf::Vector2u> get_list_squares() const;
  void display_block(Grid &);
  void hide_block(Grid &);
  bool go_down(Grid &);
  void go_right(Grid &);
  void go_left(Grid &);
  virtual void rotate(Grid &) = 0;
};

#endif //! BLOCK_HPP