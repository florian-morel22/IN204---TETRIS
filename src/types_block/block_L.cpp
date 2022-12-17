#include "../../inc/types_block/block_L.hpp"

namespace tetris {

Block_L::Block_L(int i, int j) {
  value = 3;
  rotate_value = 0;

  list_squares.push_back({i - 1, j});
  list_squares.push_back({i, j});
  list_squares.push_back({i + 1, j});
  list_squares.push_back({i + 1, j - 1});
}

void Block_L::rotate(Grid &G) {
  int i = list_squares[1].x;
  int j = list_squares[1].y;
  int next_i[4] = {0, 0, 0, 0};
  int next_j[4] = {0, 0, 0, 0};

  switch (rotate_value) {

  case 0: {
    next_i[0] = i;
    next_i[1] = i;
    next_i[2] = i;
    next_i[3] = i + 1;
    next_j[0] = j - 1;
    next_j[1] = j;
    next_j[2] = j + 1;
    next_j[3] = j + 1;
  } break;

  case 1: {
    next_i[0] = i + 1;
    next_i[1] = i;
    next_i[2] = i - 1;
    next_i[3] = i - 1;
    next_j[0] = j;
    next_j[1] = j;
    next_j[2] = j;
    next_j[3] = j + 1;
  } break;

  case 2: {
    next_i[0] = i;
    next_i[1] = i;
    next_i[2] = i;
    next_i[3] = i - 1;
    next_j[0] = j + 1;
    next_j[1] = j;
    next_j[2] = j - 1;
    next_j[3] = j - 1;
  } break;

  case 3: {
    next_i[0] = i - 1;
    next_i[1] = i;
    next_i[2] = i + 1;
    next_i[3] = i + 1;
    next_j[0] = j;
    next_j[1] = j;
    next_j[2] = j;
    next_j[3] = j - 1;
  } break;
  }

  if (G.is_empty_case(next_i[0], next_j[0], list_squares) &&
      G.is_empty_case(next_i[1], next_j[1], list_squares) &&
      G.is_empty_case(next_i[2], next_j[2], list_squares) &&
      G.is_empty_case(next_i[3], next_j[3], list_squares)) {
    list_squares.clear();
    list_squares.push_back({next_i[0], next_j[0]});
    list_squares.push_back({next_i[1], next_j[1]});
    list_squares.push_back({next_i[2], next_j[2]});
    list_squares.push_back({next_i[3], next_j[3]});
    rotate_value = (rotate_value + 1) % 4;
  }
}

} // namespace tetris