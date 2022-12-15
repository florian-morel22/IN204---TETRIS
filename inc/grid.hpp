#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "utils.hpp"

namespace tetris {

class Grid {

private:
  int nb_lines;
  int nb_columns;
  int **grid_num;
  sf::RectangleShape **grid_drawn;
  std::vector<sf::Color> list_color_block;

  template <typename TYPE_GRID> void Free_grid(TYPE_GRID, int);

public:
  auto initialize_grid(int l, int c, sf::Vector2f grid_view_size) -> void;
  auto get_size() const -> sf::Vector2i;

  auto clean_grid() -> void;
  auto clean_grid_with_borders() -> void;

  auto display_grid() const -> void;
  auto draw_grid() -> void;

  auto set_case_value(int i, int j, int newValue) -> void;
  auto get_case_value(int i, int j) const -> int;
  auto get_case_value_drawn(int i, int j) const -> sf::RectangleShape;

  auto is_empty_case(int, int, const std::vector<sf::Vector2i> &) -> bool;

  auto set_color_block(int k, sf::Color c) -> void;
  auto get_color_block(int k) const -> sf::Color;

  auto Call_Free_grid(std::string) -> void;
};

} // namespace tetris

#endif // !GRID_HPP