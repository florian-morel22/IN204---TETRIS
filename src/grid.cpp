#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cstdint>
#include <cstdio>
#include <exception>

#include "../inc/grid.hpp"
#include "../inc/game.hpp"


void Grid::initialize_grid(unsigned int c, unsigned int l){
    nb_lines = l;
    nb_columns = c;

    printf("%d, %d\n", nb_lines, nb_columns);
    

    //Allocation dynamique de la grille
    //grid = new unsigned int* [nb_columns+4];
    grid = NULL;
    if (grid==NULL) throw std::runtime_error("Allocation de mémoire pour la grille");
    for (unsigned int i=0; i < nb_columns+4; i++){
        grid[i] = new unsigned int [nb_lines+4]; 
        if (grid[i]==NULL) throw std::runtime_error("Allocation de mémoire pour la grille");
    }


    //Allocation dynamique de la grille_drawn
    grid_drawn = new sf::RectangleShape* [nb_columns];
    if (grid==NULL) throw std::runtime_error("Allocation de mémoire pour la grille");
    for (unsigned int i=0; i < nb_columns; i++){
        grid_drawn[i] = new sf::RectangleShape [nb_lines];
        if (grid[i]==NULL) throw std::runtime_error("Allocation de mémoire pour la grille");
    }
        


    for (unsigned int i=0; i<nb_columns; i++){
        for (unsigned int j=0; j<nb_lines; j++){
            grid_drawn[i][j].setSize({30/(0.7*WIN_WIDTH)*WIN_HEIGHT,30});
            // Faire en sorte que les carrés soient carrés. Utiliser des proportions
            float i_ = 40/(0.7*WIN_WIDTH)*WIN_HEIGHT*i;
            float j_ = 40*j;
            grid_drawn[i][j].setPosition({i_,j_});
        }
    }

    clean_grid_with_borders();
    clean_grid();

                    
    list_color_block.push_back({255,255,255}); // Couleur des cases vides
    list_color_block.push_back({180,167,214}); // Couleur du block I
    list_color_block.push_back({180,167,214}); // ...
    list_color_block.push_back({213,166,189}); // ..
    list_color_block.push_back({182,215,168}); // .
    list_color_block.push_back({249,203,156});
    list_color_block.push_back({234,153,153});
    
};

void Grid::clean_grid(){
    //Reinitialisation de la grille avec des 0
    for (unsigned int i=2; i < nb_columns+2; ++i)
        for (unsigned int j=2; j < nb_lines+2; ++j)
            grid[i][j] = 0;
}

void Grid::clean_grid_with_borders(){
    //Reinitialisation des bords de la grille avec des 0
    for (unsigned int i=0; i < nb_columns+4; i++)
        for (unsigned int j=0; j < nb_lines+4; j++)
        {   printf("i : %d, j : %d\n", i, j);
            grid[i][j] = 1;}
    printf("OK\n");
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
    if (grid==NULL) throw (std::runtime_error("Liberation grille"));
    for (unsigned int i=0; i < nb_columns+4; i++){
        if (grid[i]==NULL) throw (std::runtime_error("Liberation grille"));
        delete[] grid[i];
    }
    delete[] grid;
    printf("Grille libérée\n");
};


void Grid::display_grid()const{
    for (unsigned int i=0; i < nb_columns+4; ++i) {
        for (unsigned int j=0; j < nb_lines+4; ++j){
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("----------\n");
};


void Grid::draw_grid(){
    for (unsigned int i=0; i<nb_columns; ++i){
        for (unsigned int j=0; j<nb_lines; ++j){
                grid_drawn[i][j].setFillColor(get_color_block(grid[i+2][j+2]));
        }
    }
}

void Grid::set_color_block(unsigned int i, sf::Color c){
    list_color_block[i] = c;
}

sf::Color Grid::get_color_block(unsigned int k)const{
    return list_color_block[k];
};

sf::RectangleShape Grid::get_case_value_drawn(unsigned int i, unsigned int j)const{
    return grid_drawn[i][j];
}