#ifndef GRID_HPP
# define GRID_HPP

#include "../inc/block.hpp"
#include <SFML/System/Vector2.hpp>

class Grid
{

    private:
        unsigned int nb_lines;
        unsigned int nb_columns;
        unsigned int **grid;

    public:
        void initialize_grid(unsigned int l, unsigned int c);
        void clean_grid();

        void display_grid()const;
        void display_block(Block&)const;
        
        void set_case_value(unsigned int i, unsigned int j, unsigned int newValue);
        unsigned int get_case_value(unsigned int i, unsigned int j)const;
        sf::Vector2u get_size()const;
        
        void Free_grid();
        
};


#endif