#include "../../inc/types_block/block_I.hpp"
#include <SFML/System/Vector2.hpp>

namespace tetris {

Block_I::Block_I(int i, int j) {
  value = 1;
  rotate_value = 0;

  list_squares.push_back({i, j});
  list_squares.push_back({i + 1, j});
  list_squares.push_back({i + 2, j});
  list_squares.push_back({i + 3, j});
}

void Block_I::rotate(Grid &g) {
  int i = list_squares[0].x;
  int j = list_squares[0].y;
  int next_i[4] = {0, 0, 0, 0};
  int next_j[4] = {0, 0, 0, 0};

  switch (rotate_value) {

  case 0: {
    next_i[0] = i + 2;
    next_i[1] = i + 2;
    next_i[2] = i + 2;
    next_i[3] = i + 2;
    next_j[0] = j - 1;
    next_j[1] = j;
    next_j[2] = j + 1;
    next_j[3] = j + 2;
  } break;

  case 1: {
    next_i[0] = i + 1;
    next_i[1] = i;
    next_i[2] = i - 1;
    next_i[3] = i - 2;
    next_j[0] = j + 2;
    next_j[1] = j + 2;
    next_j[2] = j + 2;
    next_j[3] = j + 2;
  } break;

  case 2: {
    next_i[0] = i - 2;
    next_i[1] = i - 2;
    next_i[2] = i - 2;
    next_i[3] = i - 2;
    next_j[0] = j + 1;
    next_j[1] = j;
    next_j[2] = j - 1;
    next_j[3] = j - 2;
  } break;

  case 3: {
    next_i[0] = i - 1;
    next_i[1] = i;
    next_i[2] = i + 1;
    next_i[3] = i + 2;
    next_j[0] = j - 2;
    next_j[1] = j - 2;
    next_j[2] = j - 2;
    next_j[3] = j - 2;
  } break;
  }

  if (g.is_empty_case(next_i[0], next_j[0], list_squares) &&
      g.is_empty_case(next_i[1], next_j[1], list_squares) &&
      g.is_empty_case(next_i[2], next_j[2], list_squares) &&
      g.is_empty_case(next_i[3], next_j[3], list_squares)) {
    list_squares.clear();
    list_squares.push_back({next_i[0], next_j[0]});
    list_squares.push_back({next_i[1], next_j[1]});
    list_squares.push_back({next_i[2], next_j[2]});
    list_squares.push_back({next_i[3], next_j[3]});
    rotate_value = (rotate_value + 1) % 4;
  }
}

} // namespace tetris