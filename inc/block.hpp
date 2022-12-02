#ifndef BLOCK_HPP
# define BLOCK_HPP

#include <iostream>
#include <map>

#include <SFML/System.hpp> 
#include <SFML/System/Vector2.hpp>

#include "grid.hpp"
#include "utils.hpp"


class Block 
{
    protected: //Les classes qui en heritent en ont besoin
        
        //Position du coin haut gauche du grand carre
        sf::Vector2u _pos;

        //Donne la couleur dans la grille
        unsigned int value;

        unsigned int rotate_value = 0;

        //position de chaque carre par rapport à _pos
        std::vector<sf::Vector2u> list_squares;
    
    public:

        sf::Vector2u get_pos() const;
        void set_pos(unsigned i,unsigned j);

        unsigned int get_value()const;
        std::vector<sf::Vector2u> get_list_squares()const;

        void display_block(Grid&);

        void go_down(Grid&);
        void go_right(Grid&);
        void go_left(Grid&);

        virtual void rotate(){printf("Block testttt\n");};

};

#endif //!BLOCK_HPP