#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System.hpp>

#include "utils.hpp"

class Grid {

private:
  unsigned int nb_lines;
  unsigned int nb_columns;
  unsigned int **grid_num;
  sf::RectangleShape **grid_drawn;

  std::vector<sf::Color> list_color_block;

public:
  void initialize_grid(unsigned int l, unsigned int c);
  void clean_grid();
  void clean_grid_with_borders();
  // clean TOUTE la grille avec des 1 (appeler clean
  // grid juste apres pour ajouter les 0 au milieu)

  void display_grid() const;

  sf::RectangleShape case1;
  void draw_grid();

  void set_case_value(unsigned int i, unsigned int j, unsigned int newValue);
  unsigned int get_case_value(unsigned int i, unsigned int j) const;

  sf::RectangleShape get_case_value_drawn(unsigned int i, unsigned int j) const;

  bool empty_case(unsigned int i, unsigned int j,
                 std::vector<sf::Vector2u> list_squares);

  sf::Vector2u get_size() const;
  unsigned int **get_grid_num() const;
  sf::RectangleShape **get_grid_drawn() const;

  void set_color_block(unsigned int k, sf::Color c);
  sf::Color get_color_block(unsigned int k) const;

  template <typename type_grid>
  void Free_grid(type_grid _grid, unsigned int _nb_col) {
    if (_grid == NULL)
      throw(std::runtime_error("Liberation grille"));

    for (unsigned int i = 0; i < _nb_col; i++) {
      if (_grid[i] == NULL) {
        delete[] _grid;
        printf("Grille libérée\n");
        throw(std::runtime_error("Liberation grille"));
      }
      delete[] _grid[i];
      printf("colonne %d de la grille libérée\n", i + 1);
    }

    delete[] _grid;
    printf("Grille libérée\n");
  };
};

#endif