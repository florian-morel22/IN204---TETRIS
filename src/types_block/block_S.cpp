#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>

#include "../../inc/types_block/block_S.hpp"

Block_S::Block_S(unsigned i, unsigned j) {
  value = 5;

  rotate_value = 0;

  list_squares.push_back({i, j + 1});
  list_squares.push_back({i + 1, j + 1});
  list_squares.push_back({i + 1, j});
  list_squares.push_back({i + 2, j});
}

void Block_S::rotate(Grid &g) {
  if (rotate_value == 0) {

    unsigned int i = list_squares[0].x;
    unsigned int j = list_squares[0].y;
    if (g.empty_case(i, j - 2, list_squares) &&
        g.empty_case(i, j - 1, list_squares) &&
        g.empty_case(i + 1, j - 1, list_squares) &&
        g.empty_case(i + 1, j, list_squares)) {
      list_squares.clear();
      list_squares.push_back({i, j - 2});
      list_squares.push_back({i, j - 1});
      list_squares.push_back({i + 1, j - 1});
      list_squares.push_back({i + 1, j});
      rotate_value++;
    }
  }

  else if (rotate_value == 1) {

    unsigned int i = list_squares[0].x;
    unsigned int j = list_squares[0].y;
    if (g.empty_case(i + 2, j, list_squares) &&
        g.empty_case(i + 1, j, list_squares) &&
        g.empty_case(i + 1, j + 1, list_squares) &&
        g.empty_case(i, j + 1, list_squares)) {
      list_squares.clear();
      list_squares.push_back({i + 2, j});
      list_squares.push_back({i + 1, j});
      list_squares.push_back({i + 1, j + 1});
      list_squares.push_back({i, j + 1});
      rotate_value++;
    }
  }

  else if (rotate_value == 2) {

    unsigned int i = list_squares[0].x;
    unsigned int j = list_squares[0].y;
    if (g.empty_case(i, j + 2, list_squares) &&
        g.empty_case(i, j + 1, list_squares) &&
        g.empty_case(i - 1, j + 1, list_squares) &&
        g.empty_case(i - 1, j, list_squares)) {
      list_squares.clear();
      list_squares.push_back({i, j + 2});
      list_squares.push_back({i, j + 1});
      list_squares.push_back({i - 1, j + 1});
      list_squares.push_back({i - 1, j});

      rotate_value++;
    }
  }

  else if (rotate_value == 3) {

    unsigned int i = list_squares[0].x;
    unsigned int j = list_squares[0].y;
    if (g.empty_case(i - 2, j, list_squares) &&
        g.empty_case(i - 1, j, list_squares) &&
        g.empty_case(i - 1, j - 1, list_squares) &&
        g.empty_case(i, j - 1, list_squares)) {
      list_squares.clear();
      list_squares.push_back({i - 2, j});
      list_squares.push_back({i - 1, j});
      list_squares.push_back({i - 1, j - 1});
      list_squares.push_back({i, j - 1});

      rotate_value = 0;
    }
  }
}