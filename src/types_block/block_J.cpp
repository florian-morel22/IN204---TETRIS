#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>

#include "../../inc/types_block/block_J.hpp"

Block_J::Block_J(unsigned i, unsigned j) {
  value = 2;
  rotate_value = 0;

  list_squares.push_back({i - 1, j - 1});
  list_squares.push_back({i - 1, j});
  list_squares.push_back({i, j});
  list_squares.push_back({i + 1, j});
}

void Block_J::rotate(Grid &G) {
  if (rotate_value == 0) {

    unsigned int i = list_squares[2].x;
    unsigned int j = list_squares[2].y;
    if (G.empty_case(i + 1, j - 1, list_squares) &&
        G.empty_case(i, j - 1, list_squares) &&
        G.empty_case(i, j, list_squares) &&
        G.empty_case(i, j + 1, list_squares)) {
      list_squares.clear();
      list_squares.push_back({i + 1, j - 1});
      list_squares.push_back({i, j - 1});
      list_squares.push_back({i, j});
      list_squares.push_back({i, j + 1});
      rotate_value++;
    }

  }

  else if (rotate_value == 1) {

    unsigned int i = list_squares[2].x;
    unsigned int j = list_squares[2].y;
    if (G.empty_case(i + 1, j + 1, list_squares) &&
        G.empty_case(i + 1, j, list_squares) &&
        G.empty_case(i, j, list_squares) &&
        G.empty_case(i - 1, j, list_squares)) {
      list_squares.clear();
      list_squares.push_back({i + 1, j + 1});
      list_squares.push_back({i + 1, j});
      list_squares.push_back({i, j});
      list_squares.push_back({i - 1, j});
      rotate_value++;
    }
  }

  else if (rotate_value == 2) {

    unsigned int i = list_squares[2].x;
    unsigned int j = list_squares[2].y;
    if (G.empty_case(i - 1, j + 1, list_squares) &&
        G.empty_case(i, j + 1, list_squares) &&
        G.empty_case(i, j, list_squares) &&
        G.empty_case(i, j - 1, list_squares)) {
      list_squares.clear();
      list_squares.push_back({i - 1, j + 1});
      list_squares.push_back({i, j + 1});
      list_squares.push_back({i, j});
      list_squares.push_back({i, j - 1});
      rotate_value++;
    }
  }

  else if (rotate_value == 3) {

    unsigned int i = list_squares[2].x;
    unsigned int j = list_squares[2].y;
    if (G.empty_case(i - 1, j - 1, list_squares) &&
        G.empty_case(i - 1, j, list_squares) &&
        G.empty_case(i, j, list_squares) &&
        G.empty_case(i + 1, j, list_squares)) {
      list_squares.clear();
      list_squares.push_back({i - 1, j - 1});
      list_squares.push_back({i - 1, j});
      list_squares.push_back({i, j});
      list_squares.push_back({i + 1, j});
      rotate_value = 0;
    }
  }
}