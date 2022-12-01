#ifndef GRID_HPP
# define GRID_HPP


#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>


class Grid
{

    private:
        unsigned int nb_lines;
        unsigned int nb_columns;
        unsigned int **grid;
        sf::RectangleShape **grid_drawn;

        std::vector<sf::Color> list_color_block;

    public:
        void initialize_grid(unsigned int l, unsigned int c);
        void clean_grid();
        void clean_grid_with_borders(); // clean TOUTE la grille avec des 1 (appeler clean grid juste apres pour ajouter les 0 au milieu)

        void display_grid()const;
        

        sf::RectangleShape case1;
        void draw_grid();
        
        void set_case_value(unsigned int i, unsigned int j, unsigned int newValue);
        unsigned int get_case_value(unsigned int i, unsigned int j)const;

        sf::RectangleShape get_case_value_drawn(unsigned int i, unsigned int j)const;
        
        sf::Vector2u get_size()const;

        void set_color_block(unsigned int k, sf::Color c);
        sf::Color get_color_block(unsigned int k)const;

        
        void Free_grid();
        
};


#endif