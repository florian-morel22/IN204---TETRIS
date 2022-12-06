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
    grid_num = new unsigned int* [nb_columns+4];
    if (grid_num==NULL) throw std::runtime_error("Allocation de mémoire pour la grille");
    for (unsigned int i=0; i < nb_columns+4; i++){
        grid_num[i] = new unsigned int [nb_lines+4]; 
        if (grid_num[i]==NULL) throw std::runtime_error("Allocation de mémoire pour la grille");
    }


    //Allocation dynamique de la grille_drawn (Grille graphique)
    grid_drawn = new sf::RectangleShape* [nb_columns];
    if (grid_drawn==NULL) throw std::runtime_error("Allocation de mémoire pour la grille_drawn");
    for (unsigned int i=0; i < nb_columns; i++){
        grid_drawn[i] = new sf::RectangleShape [nb_lines];
        if (grid_drawn[i]==NULL) throw std::runtime_error("Allocation de mémoire pour la grille_drawn");
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
    list_color_block.push_back({180,167,189}); // ...
    list_color_block.push_back({213,166,189}); // ..
    list_color_block.push_back({182,215,168}); // .
    list_color_block.push_back({249,203,156});
    list_color_block.push_back({234,153,153});
    
};

void Grid::clean_grid(){
    //Reinitialisation de la grille avec des 0
    for (unsigned int i=2; i < nb_columns+2; ++i)
        for (unsigned int j=2; j < nb_lines+2; ++j)
            grid_num[i][j] = 0;
}

void Grid::clean_grid_with_borders(){
    //Reinitialisation des bords de la grille avec des 0
    for (unsigned int i=0; i < nb_columns+4; i++)
        for (unsigned int j=0; j < nb_lines+4; j++)
            grid_num[i][j] = 1;

}



void Grid::set_case_value(unsigned int i, unsigned int j, unsigned int newValue){
    grid_num[i][j] = newValue;
};

unsigned int Grid::get_case_value(unsigned int i, unsigned int j)const{
    return grid_num[i][j];
};

sf::Vector2u Grid::get_size()const{
    return {nb_columns, nb_lines};
};

/*template<typename type_grid>
void Grid::Free_grid(type_grid _grid, unsigned int _nb_col){
    if (_grid==NULL) throw (std::runtime_error("Liberation grille"));
    
    for (unsigned int i=0; i < _nb_col ; i++){
        if (_grid[i]==NULL) {
            delete[] _grid;
            printf("Grille libérée\n");
            throw (std::runtime_error("Liberation grille"));
        }
            delete[] _grid[i];
        printf("colonne %d de la grille libérée\n", i+1);
    }

    delete[] _grid;
    printf("Grille libérée\n");
};*/


void Grid::display_grid()const{
    for (unsigned int i=0; i < nb_columns+4; ++i) {
        for (unsigned int j=0; j < nb_lines+4; ++j){
            printf("%d ", grid_num[i][j]);
        }
        printf("\n");
    }
    printf("----------\n");
};


void Grid::draw_grid(){
    for (unsigned int i=0; i<nb_columns; ++i){
        for (unsigned int j=0; j<nb_lines; ++j){
                grid_drawn[i][j].setFillColor(get_color_block(grid_num[i+2][j+2]));
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

unsigned int** Grid::get_grid_num()const{
    return grid_num;
};

sf::RectangleShape** Grid::get_grid_drawn()const{
    return grid_drawn;
};

bool Grid::free_case(unsigned int i, unsigned int j, std::vector<sf::Vector2u> list_squares){
    if (get_case_value(i, j)==0 || find_vector(list_squares, {i,j}))
        return true;
    else 
        return false;
}