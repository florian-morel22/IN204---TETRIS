#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../inc/block.hpp"

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

unsigned int Block::get_height() const {
    return height;
};

unsigned int Block::get_width() const {
    return width;
};

unsigned int Block::get_value()const{
    return value;
}

std::vector<sf::Vector2u> Block::get_list_squares()const{
    return list_squares;
};


void Block::go_down(){
    _pos.x = _pos.x+1;
};
void Block::go_right(){
    _pos.y = _pos.y+1;
};
void Block::go_left(){
    _pos.y = _pos.y-1;
};



Block_cube::Block_cube(unsigned i,unsigned j):Block( i, j)
{
    value = 1;

    height = 2;
    width = 2;

    list_squares.push_back({0,0});
    list_squares.push_back({0,1});
    list_squares.push_back({1,0});
    list_squares.push_back({1,1});

};