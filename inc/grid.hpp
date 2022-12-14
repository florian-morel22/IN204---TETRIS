#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/System/Vector2.hpp>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System.hpp>

#include "utils.hpp"

namespace tetris{


class Grid {

	private:
		int nb_lines;
		int nb_columns;
		int **grid_num;
		sf::RectangleShape **grid_drawn;
		std::vector<sf::Color> list_color_block;

		template <typename TYPE_GRID>
		void Free_grid(TYPE_GRID, int);

	public:
		void initialize_grid(int l, int c, sf::Vector2f grid_view_size);
		void clean_grid();
		void clean_grid_with_borders();
		// clean TOUTE la grille avec des 1 (appeler clean
		// grid juste apres pour ajouter les 0 au milieu)

		void display_grid() const;

		sf::RectangleShape case1;
		void draw_grid();

		void set_case_value(int i, int j, int newValue);
		int get_case_value(int i, int j) const;

		sf::RectangleShape get_case_value_drawn(int i, int j) const;

		bool empty_case(int, int, const std::vector<sf::Vector2i> &);

		sf::Vector2i get_size() const;
		sf::RectangleShape **get_grid_drawn() const;

		void set_color_block(int k, sf::Color c);
		sf::Color get_color_block(int k) const;

		void Call_Free_grid(std::string);
};


} // !namespace tetris

#endif // !GRID_HPP