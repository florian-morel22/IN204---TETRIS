#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cstdint>
#include <cstdio>

#include "../inc/grid.hpp"
#include "game.hpp"


void Grid::initialize_grid(unsigned int c, unsigned int l){
    nb_lines = l;
    nb_columns = c;
    
    //Allocation dynamique de la grille
    grid = new unsigned int* [ nb_columns ];
    //Gérer si grid = NULL
    for (unsigned int i=0; i < nb_columns; i++)
        grid[i] = new unsigned int [nb_lines]; //!!

    //Allocation dynamique de la grille_drawn
    grid_drawn = new sf::RectangleShape* [ nb_columns ];
    //Gérer si grid = NULL
    for (unsigned int i=0; i < nb_columns; i++)
        grid_drawn[i] = new sf::RectangleShape [nb_lines];//!!


    for (unsigned int i=0; i<nb_columns; i++){
        for (unsigned int j=0; j<nb_lines; j++){
            grid_drawn[i][j].setSize({30/(0.7*WIN_WIDTH)*WIN_HEIGHT,30});
            // Faire en sorte que les carrés soient carrés. Utiliser des proportions
            float i_ = 40/(0.7*WIN_WIDTH)*WIN_HEIGHT*i;
            float j_ = 40*j;
            grid_drawn[i][j].setPosition({i_,j_});
        }
    }
};

void Grid::clean_grid(){
    //Reinitialisation de la grille avec des 0
    for (unsigned int i=0; i < nb_columns; i++)
        for (unsigned int j=0; j < nb_lines; j++)
            grid[i][j] = 0;
}



void Grid::set_case_value(unsigned int i, unsigned int j, unsigned int newValue){
    grid[i][j] = newValue;
};

unsigned int Grid::get_case_value(unsigned int i, unsigned int j)const{
    return grid[i][j];
};

sf::Vector2u Grid::get_size()const{
    return {nb_columns, nb_lines};
};


void Grid::Free_grid(){
    for (unsigned int i=0; i < nb_columns; i++)
        delete[] grid[i];
    delete[] grid;
    printf("Grille libérée\n");
};


void Grid::display_grid()const{
    for (unsigned int i=0; i < nb_columns; i++) {
        for (unsigned int j=0; j < nb_lines; j++){
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("----------\n");
};


void Grid::draw_grid(){
    for (unsigned int i=0; i<nb_columns; i++){
        for (unsigned int j=0; j<nb_lines; j++){
            if(grid[i][j]==0)
                grid_drawn[i][j].setFillColor(sf::Color{255,255,255});
            if(grid[i][j]==1)
                grid_drawn[i][j].setFillColor(sf::Color{180,167,214});
            if(grid[i][j]==2)
                grid_drawn[i][j].setFillColor(sf::Color{180,167,214});
            if(grid[i][j]==3)
                grid_drawn[i][j].setFillColor(sf::Color{213,166,189});
            if(grid[i][j]==4)
                grid_drawn[i][j].setFillColor(sf::Color{182,215,168});
            if(grid[i][j]==5)
                grid_drawn[i][j].setFillColor(sf::Color{249,203,156});
            if(grid[i][j]==6)
                grid_drawn[i][j].setFillColor(sf::Color{234,153,153});
        }
    }
}

sf::RectangleShape Grid::get_case_value_drawn(unsigned int i, unsigned int j)const{
    return grid_drawn[i][j];
}