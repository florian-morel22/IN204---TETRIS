#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>

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
  if (rotate_value == 0) {

    int i = list_squares[1].x;
    int j = list_squares[1].y;
    if (G.is_empty_case(i, j - 1, list_squares) &&
        G.is_empty_case(i, j, list_squares) &&
        G.is_empty_case(i, j + 1, list_squares) &&
        G.is_empty_case(i + 1, j + 1, list_squares)) {
      list_squares.clear();
      list_squares.push_back({i, j - 1});
      list_squares.push_back({i, j});
      list_squares.push_back({i, j + 1});
      list_squares.push_back({i + 1, j + 1});
      rotate_value++;
    }
  }

  else if (rotate_value == 1) {

    int i = list_squares[1].x;
    int j = list_squares[1].y;
    if (G.is_empty_case(i + 1, j, list_squares) &&
        G.is_empty_case(i, j, list_squares) &&
        G.is_empty_case(i - 1, j, list_squares) &&
        G.is_empty_case(i - 1, j + 1, list_squares)) {
      list_squares.clear();
      list_squares.push_back({i + 1, j});
      list_squares.push_back({i, j});
      list_squares.push_back({i - 1, j});
      list_squares.push_back({i - 1, j + 1});
      rotate_value++;
    }
  }

  else if (rotate_value == 2) {

    int i = list_squares[1].x;
    int j = list_squares[1].y;
    if (G.is_empty_case(i, j + 1, list_squares) &&
        G.is_empty_case(i, j, list_squares) &&
        G.is_empty_case(i, j - 1, list_squares) &&
        G.is_empty_case(i - 1, j - 1, list_squares)) {
      list_squares.clear();
      list_squares.push_back({i, j + 1});
      list_squares.push_back({i, j});
      list_squares.push_back({i, j - 1});
      list_squares.push_back({i - 1, j - 1});
      rotate_value++;
    }
  }

  else if (rotate_value == 3) {

    int i = list_squares[1].x;
    int j = list_squares[1].y;
    if (G.is_empty_case(i - 1, j, list_squares) &&
        G.is_empty_case(i, j, list_squares) &&
        G.is_empty_case(i + 1, j, list_squares) &&
        G.is_empty_case(i + 1, j - 1, list_squares)) {
      list_squares.clear();
      list_squares.push_back({i - 1, j});
      list_squares.push_back({i, j});
      list_squares.push_back({i + 1, j});
      list_squares.push_back({i + 1, j - 1});
      rotate_value = 0;
    }
  }
}

} // namespace tetris