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

    public:
        void initialize_grid(unsigned int l, unsigned int c);
        void clean_grid();

        void display_grid()const;
        

        sf::RectangleShape case1;
        void draw_grid();
        
        void set_case_value(unsigned int i, unsigned int j, unsigned int newValue);
        unsigned int get_case_value(unsigned int i, unsigned int j)const;

        sf::RectangleShape get_case_value_drawn(unsigned int i, unsigned int j)const;
        
        sf::Vector2u get_size()const;

        
        void Free_grid();
        
};


#endif