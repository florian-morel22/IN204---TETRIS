#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../inc/block_I.hpp"

Block_I::Block_I(unsigned i,unsigned j):Block( i, j)
{
    value = 1;

    rotate_value = 0;

    list_squares.push_back({i,j});
    list_squares.push_back({i+1,j});
    list_squares.push_back({i+2,j});
    list_squares.push_back({i+3,j});
}

void Block_I::rotate(){
    printf("Block_bar testtttt");
    if (rotate_value == 0){

        unsigned int i = list_squares[0].x;
        unsigned int j = list_squares[0].y;
        list_squares.clear();
        list_squares.push_back({i+1,j+2});
        list_squares.push_back({i,j+2});
        list_squares.push_back({i-1,j+2});
        list_squares.push_back({i-2,j+2});
       
        rotate_value++;
    }

    else if (rotate_value == 1){

        unsigned int i = list_squares[0].x;
        unsigned int j = list_squares[0].y;
        list_squares.clear();
        list_squares.push_back({i+2,j+1});
        list_squares.push_back({i+2,j});
        list_squares.push_back({i+2,j-1});
        list_squares.push_back({i+2,j-2});
       
        rotate_value++;
    }
}