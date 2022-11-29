#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cstdio>

#include "../inc/grid.hpp"


void Grid::initialize_grid(unsigned int l, unsigned int c){
    nb_lines = l;
    nb_columns = c;
    
    //Allocation dynamique de la grille
    grid = new unsigned int* [ nb_lines ];
    //Gérer si grid = NULL
    for (unsigned int i=0; i < nb_lines; i++)
        grid[i] = new unsigned int [nb_columns];

    //Allocation dynamique de la grille
    grid_drawn = new sf::RectangleShape* [ nb_lines ];
    //Gérer si grid = NULL
    for (unsigned int i=0; i < nb_lines; i++)
        grid_drawn[i] = new sf::RectangleShape [nb_columns];


    for (unsigned int i=0; i<nb_lines; i++){
        for (unsigned int j=0; j<nb_columns; j++){
            grid_drawn[i][j].setSize({50,50});
            // Faire en sorte que les carrés soient carrés. Utiliser des proportions
            float i_ = 55*j;
            float j_ = 55*i;
            grid_drawn[i][j].setPosition({i_,j_});
        }
    }
};

void Grid::clean_grid(){
    //Reinitialisation de la grille avec des 0
    for (unsigned int i=0; i < nb_lines; i++)
        for (unsigned int j=0; j < nb_columns; j++)
            grid[i][j] = 0;
}



void Grid::set_case_value(unsigned int i, unsigned int j, unsigned int newValue){
    grid[i][j] = newValue;
};

unsigned int Grid::get_case_value(unsigned int i, unsigned int j)const{
    return grid[i][j];
};

sf::Vector2u Grid::get_size()const{
    return {nb_lines, nb_columns};
};


void Grid::Free_grid(){
    for (unsigned int i=0; i < nb_lines; i++)
        delete[] grid[i];
    delete[] grid;
    printf("Grille libérée\n");
};


void Grid::display_grid()const{
    for (unsigned int i=0; i < nb_lines; i++) {
        for (unsigned int j=0; j < nb_columns; j++){
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("----------\n");
};


void Grid::display_block(Block &b)const {
    for(size_t k=0; k<b.get_list_squares().size();k++){
        unsigned int i = b.get_list_squares()[k].x;
        unsigned int j = b.get_list_squares()[k].y;
        sf::Vector2u pos = b.get_pos();
        grid[(pos.x+i)%nb_lines][pos.y+j] = b.get_value(); 
    }
}

void Grid::draw_grid(){
    for (unsigned int i=0; i<nb_lines; i++){
        for (unsigned int j=0; j<nb_columns; j++){
            if(grid[i][j]>0)
                grid_drawn[i][j].setFillColor(sf::Color::White);
            else
                grid_drawn[i][j].setFillColor(sf::Color::Black);
        }
    }
}

sf::RectangleShape Grid::get_case_value_drawn(unsigned int i, unsigned int j)const{
    return grid_drawn[i][j];
}

