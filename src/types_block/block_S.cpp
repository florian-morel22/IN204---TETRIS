#include "../../inc/types_block/block_S.hpp"

namespace tetris {

Block_S::Block_S(int i, int j) {
  value = 5;
  rotate_value = 0;

  list_squares.push_back({i, j + 1});
  list_squares.push_back({i + 1, j + 1});
  list_squares.push_back({i + 1, j});
  list_squares.push_back({i + 2, j});
}

void Block_S::rotate(Grid &g) {
  int i = list_squares[0].x;
  int j = list_squares[0].y;
  int next_i[4] = {0, 0, 0, 0};
  int next_j[4] = {0, 0, 0, 0};

  switch (rotate_value) {

  case 0: {
    next_i[0] = i;
    next_i[1] = i;
    next_i[2] = i + 1;
    next_i[3] = i + 1;
    next_j[0] = j - 2;
    next_j[1] = j - 1;
    next_j[2] = j - 1;
    next_j[3] = j;
  } break;

  case 1: {
    next_i[0] = i + 2;
    next_i[1] = i + 1;
    next_i[2] = i + 1;
    next_i[3] = i;
    next_j[0] = j;
    next_j[1] = j;
    next_j[2] = j + 1;
    next_j[3] = j + 1;
  } break;

  case 2: {
    next_i[0] = i;
    next_i[1] = i;
    next_i[2] = i - 1;
    next_i[3] = i - 1;
    next_j[0] = j + 2;
    next_j[1] = j + 1;
    next_j[2] = j + 1;
    next_j[3] = j;
  } break;

  case 3: {
    next_i[0] = i - 2;
    next_i[1] = i - 1;
    next_i[2] = i - 1;
    next_i[3] = i;
    next_j[0] = j;
    next_j[1] = j;
    next_j[2] = j - 1;
    next_j[3] = j - 1;
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