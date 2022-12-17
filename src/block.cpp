#include "../inc/block.hpp"

namespace tetris {

int Block::get_value() const { return value; }

std::vector<sf::Vector2i> Block::get_list_squares() const {
  return list_squares;
};

void Block::display_block(Grid &G, int offset_i, int offset_j) {
  for (size_t k = 0; k < list_squares.size(); k++) {
    int i = list_squares[k].x + offset_i;
    int j = list_squares[k].y + offset_j;
    G.set_case_value(i, j, value);
  }
}

void Block::hide_block(Grid &G) {
  for (size_t k = 0; k < list_squares.size(); k++) {
    int i = list_squares[k].x;
    int j = list_squares[k].y;
    G.set_case_value(i, j, 0);
  }
}

bool Block::go_down(Grid &G) {
  bool is_go_down = true;

  for (size_t k = 0; k < list_squares.size(); k++) {
    int i_ = list_squares[k].x;
    int j_ = list_squares[k].y;
    if (!G.is_empty_case(i_, j_ + 1, list_squares)) {
      is_go_down = false;
    }
  }
  if (is_go_down) {
    for (size_t k = 0; k < list_squares.size(); k++) {
      list_squares[k].y += 1;
    }
  }
  return is_go_down;
};

void Block::go_right(Grid &G) {
  bool is_go_right = true;

  for (size_t k = 0; k < list_squares.size(); k++) {
    int i_ = list_squares[k].x;
    int j_ = list_squares[k].y;
    if (!G.is_empty_case(i_ + 1, j_, list_squares)) {
      is_go_right = false;
    }
  }
  if (is_go_right) {
    for (size_t k = 0; k < list_squares.size(); k++) {
      list_squares[k].x += 1;
    }
  }
};

void Block::go_left(Grid &G) {

  bool is_go_left = true;

  for (size_t k = 0; k < list_squares.size(); k++) {
    int i_ = list_squares[k].x;
    int j_ = list_squares[k].y;
    if (!G.is_empty_case(i_ - 1, j_, list_squares)) {
      is_go_left = false;
    }
  }
  if (is_go_left) {
    for (size_t k = 0; k < list_squares.size(); k++) {
      list_squares[k].x += -1;
    }
  }
};

} // namespace tetris