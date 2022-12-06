#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>

#include "../inc/block.hpp"

unsigned int Block::get_value() const { return value; }

std::vector<sf::Vector2u> Block::get_list_squares() const {
  return list_squares;
};

void Block::display_block(Grid &G) {
  for (size_t k = 0; k < list_squares.size(); k++) {
    unsigned int i = list_squares[k].x;
    unsigned int j = list_squares[k].y;
    G.set_case_value(i, j, value);
  }
}

void Block::hide_block(Grid &G) {
  for (size_t k = 0; k < list_squares.size(); k++) {
    unsigned int i = list_squares[k].x;
    unsigned int j = list_squares[k].y;
    G.set_case_value(i, j, 0);
  }
}

bool Block::go_down(Grid &G) {
  bool is_go_down = true;

  for (unsigned int k = 0; k < list_squares.size(); k++) {
    unsigned int i_ = list_squares[k].x;
    unsigned int j_ = list_squares[k].y;
    if (G.get_case_value(i_, j_ + 1) != 0 &&
        !find_vector(list_squares, {i_, j_ + 1})) {
      is_go_down = false;
    }
  }
  if (is_go_down) {
    for (unsigned int k = 0; k < list_squares.size(); k++) {
      list_squares[k].y += 1;
    }
  } else
    printf("kéblo ! Generer un nouveau block !\n");
  return is_go_down;
};

void Block::go_right(Grid &G) {
  bool is_go_right = true;

  for (unsigned int k = 0; k < list_squares.size(); k++) {
    unsigned int i_ = list_squares[k].x;
    unsigned int j_ = list_squares[k].y;
    if (G.get_case_value(i_ + 1, j_) != 0 &&
        !find_vector(list_squares, {i_ + 1, j_})) {
      is_go_right = false;
    }
  }
  if (is_go_right) {
    for (unsigned int k = 0; k < list_squares.size(); k++) {
      list_squares[k].x += 1;
    }
  } else
    printf("kéblo !\n");
};

void Block::go_left(Grid &G) {

  bool is_go_left = true;

  for (unsigned int k = 0; k < list_squares.size(); k++) {
    unsigned int i_ = list_squares[k].x;
    unsigned int j_ = list_squares[k].y;
    if (G.get_case_value(i_ - 1, j_) != 0 &&
        !find_vector(list_squares, {i_ - 1, j_})) {
      is_go_left = false;
    }
  }
  if (is_go_left) {
    for (unsigned int k = 0; k < list_squares.size(); k++) {
      list_squares[k].x += -1;
    }
  } else
    printf("kéblo !\n");
};