#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../inc/block_L.hpp"

Block_L::Block_L(unsigned i,unsigned j):Block( i, j)
{
    value = 3;

    rotate_value = 0;

    list_squares.push_back({i,j});
    list_squares.push_back({i+1,j});
    list_squares.push_back({i+2,j});
    list_squares.push_back({i,j+1});
}

void Block_L::rotate(){
    if (rotate_value == 0){

        unsigned int i = list_squares[0].x;
        unsigned int j = list_squares[0].y;
        list_squares.clear();
        list_squares.push_back({i,j-1});
        list_squares.push_back({i+1,j-1});
        list_squares.push_back({i+1,j});
        list_squares.push_back({i+1,j+1});
       
        rotate_value++;
    }

    else if (rotate_value == 1){

        unsigned int i = list_squares[0].x;
        unsigned int j = list_squares[0].y;
        list_squares.clear();
        list_squares.push_back({i+2,j});
        list_squares.push_back({i,j+1});
        list_squares.push_back({i+1,j+1});
        list_squares.push_back({i+2,j+1});
       
        rotate_value++;
    }

    else if (rotate_value == 2){

        unsigned int i = list_squares[0].x;
        unsigned int j = list_squares[0].y;
        list_squares.clear();
        list_squares.push_back({i-1,j});
        list_squares.push_back({i-1,j+1});
        list_squares.push_back({i-1,j+2});
        list_squares.push_back({i,j+2});
       
        rotate_value++;
    }

    else if (rotate_value ==3) {

        unsigned int i = list_squares[0].x;
        unsigned int j = list_squares[0].y;
        list_squares.clear();
        list_squares.push_back({i-1,j+1});
        list_squares.push_back({i,j+1});
        list_squares.push_back({i+1,j+1});
        list_squares.push_back({i-1,j+2});

        rotate_value=0;

    }

}