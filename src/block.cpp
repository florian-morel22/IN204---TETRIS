#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../inc/block.hpp"
#include "../inc/utils.hpp"

Block::Block(unsigned int i,unsigned int j)
{
    _pos.x = i;
    _pos.y = j;
};


sf::Vector2u Block::get_pos()const{
    return _pos;
};

void Block::set_pos(unsigned int i,unsigned int j){
    _pos.x = i;
    _pos.y = j;
};

unsigned int Block::get_value()const{
    return value;
}

std::vector<sf::Vector2u> Block::get_list_squares()const{
    return list_squares;
};


void Block::go_down(){
    for (int k = 0; k<list_squares.size(); k++){
        list_squares[k].x+=1;
    }
};

void Block::go_right(){
    for (int k = 0; k<list_squares.size(); k++){
        list_squares[k].y+=1;
    }
};

void Block::go_left(){
    for (int k = 0; k<list_squares.size(); k++){
        list_squares[k].y-=1;
    }
};