#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../../inc/types_block/block_L.hpp"
#include "grid.hpp"

Block_L::Block_L(unsigned i,unsigned j)
{
    value = 3;

    rotate_value = 0;

    list_squares.push_back({i,j});
    list_squares.push_back({i+1,j});
    list_squares.push_back({i+2,j});
    list_squares.push_back({i,j+1});
}

void Block_L::rotate(Grid &G){
    if (rotate_value == 0){
        
        unsigned int i = list_squares[0].x;
        unsigned int j = list_squares[0].y;
        if(G.get_case_value(i, j-1)!=0 && !find_vector(list_squares, {i,j-1}) && G.get_case_value(i+1, j-1)!=0 && !find_vector(list_squares, {i+1,j-1}) &&
           G.get_case_value(i+1, j)!=0 && !find_vector(list_squares, {i+1,j}) && G.get_case_value(i+1, j+1)!=0 && !find_vector(list_squares, {i+1,j+1}) ){
            list_squares.clear();
            list_squares.push_back({i,j-1});
            list_squares.push_back({i+1,j-1});
            list_squares.push_back({i+1,j});
            list_squares.push_back({i+1,j+1});
            rotate_value++;
        }
    }

    else if (rotate_value == 1){

        unsigned int i = list_squares[0].x;
        unsigned int j = list_squares[0].y;
        if(G.get_case_value(i+2, j)!=0 && !find_vector(list_squares, {i+2,j}) && G.get_case_value(i, j+1)!=0 && !find_vector(list_squares, {i,j+1}) &&
           G.get_case_value(i+1, j+1)!=0 && !find_vector(list_squares, {i+1,j+1}) && G.get_case_value(i+2, j+1)!=0 && !find_vector(list_squares, {i+2,j+1}) ){
            list_squares.clear();
            list_squares.push_back({i+2,j});
            list_squares.push_back({i,j+1});
            list_squares.push_back({i+1,j+1});
            list_squares.push_back({i+2,j+1});
            rotate_value++;
        }
    }

    else if (rotate_value == 2){

        unsigned int i = list_squares[0].x;
        unsigned int j = list_squares[0].y;
        if(G.get_case_value(i-1, j)!=0 && !find_vector(list_squares, {i-1,j}) && G.get_case_value(i-1, j+1)!=0 && !find_vector(list_squares, {i-1,j+1}) &&
           G.get_case_value(i+1, j+1)!=0 && !find_vector(list_squares, {i+1,j+1}) && G.get_case_value(i-1, j+2)!=0 && !find_vector(list_squares, {i-1,j+2}) ){
            list_squares.clear();
            list_squares.push_back({i-1,j});
            list_squares.push_back({i-1,j+1});
            list_squares.push_back({i-1,j+2});
            list_squares.push_back({i,j+2});
            rotate_value++;
        }
    }

    else if (rotate_value ==3) {

        unsigned int i = list_squares[0].x;
        unsigned int j = list_squares[0].y;
        if(G.get_case_value(i-1, j+1)!=0 && !find_vector(list_squares, {i-1,j+1}) && G.get_case_value(i, j+1)!=0 && !find_vector(list_squares, {i,j+1}) &&
           G.get_case_value(i+1, j+1)!=0 && !find_vector(list_squares, {i+1,j+1}) && G.get_case_value(i-1, j+2)!=0 && !find_vector(list_squares, {i-1,j+2}) ){
            list_squares.clear();
            list_squares.push_back({i-1,j+1});
            list_squares.push_back({i,j+1});
            list_squares.push_back({i+1,j+1});
            list_squares.push_back({i-1,j+2});
            rotate_value=0;
        }
    }

}