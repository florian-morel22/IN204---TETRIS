#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdio>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

#include "../inc/game.hpp"
#include "block_I.hpp"




void Game::Run(){
    Initialize();
    while(_running)
        Frame();
    Shutdown();
}

void Game::Initialize(){
    printf("Initialisation\n");
    window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "TETRIS", sf::Style::Close);
    window.setVerticalSyncEnabled(true); //Optimisation de la fenetre

    //Création de 2 vues côtes a côte : a gauche la grille, a droite le menu
    grid_view.setViewport(sf::FloatRect(0.f, 0.f, 0.7f, 1.f));
    menu_view.setViewport(sf::FloatRect(0.7f, 0.f, 0.3f, 1.f));

    bgGrid_.setSize(grid_view.getSize());
    bgGrid_.setFillColor(sf::Color::Red);
    bgMenu_.setSize(menu_view.getSize());
    bgMenu_.setFillColor(sf::Color::Green);

    // Création et initialisation de la grille
    grid.initialize_grid(20, 10);
    grid.clean_grid();

    // Création du frame rate
    fps_grid = 1;

    //Creation d'un block (A SUPPR)
    /*Block_bar block_test(0, 1);
    list_Blocks.push_back(block_test);*/


    current_block = new Block_I(0,1);
    grid.display_block(*current_block);
    grid.display_grid();

}


void Game::Shutdown(){
    grid.Free_grid();
    window.close();
    printf("Fermeture\n");
}


void Game::Frame(){


    //Gestion de des events utilisateurs
    sf::Event event;
        while (window.pollEvent(event))
        {
            InputHandler(event, *this, *current_block);
        }

    //On affiche tout !
    
    if(clock.getElapsedTime().asMilliseconds()>(1000/fps_grid)){
        
        current_block->go_down();
        grid.clean_grid();
        grid.display_block(*current_block);
        grid.display_grid();
        
        clock.restart();
    }
    

    window.clear();
    
    window.setView(grid_view);
    window.draw(bgGrid_);

    //a suppr
    grid.draw_grid();
    for (unsigned int i=0; i<grid.get_size().x; i++){
        for (unsigned int j=0; j<grid.get_size().y; j++){
            window.draw(grid.get_case_value_drawn(i, j));
        }
    }

    window.setView(menu_view);
    window.draw(bgMenu_);

    window.display();
}



void Game::set_running(bool new_running){
    _running = new_running;
}

void Game::set_fps_grid(float new_fps_grid){
    fps_grid = new_fps_grid;
}

Block Game::get_current_Block()const{
    return *current_block;
}

Grid Game::get_grid()const{
    return grid;
}


void InputHandler(sf::Event event, Game &game, Block &current_block/*, sf::RenderWindow& window*/){
    
    if (event.type == sf::Event::Closed)
            game.set_running(false);            
    if (event.type == sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::Down)
            game.set_fps_grid(10);
        if (event.key.code == sf::Keyboard::Right){/*
            sf::Vector2u p = current_block.get_pos();
            if(p.y + current_block.get_width()<game.get_grid().get_size().y){
                current_block.go_right();
                game.get_grid().clean_grid();
                game.get_grid().display_block(current_block);
                game.get_grid().display_grid();
            }
        */}
        if (event.key.code == sf::Keyboard::Left){/*
            sf::Vector2u p = current_block.get_pos();
            if(p.y>0){
                current_block.go_left();
                game.get_grid().clean_grid();
                game.get_grid().display_block(current_block);
                game.get_grid().display_grid();
            }
        */}
        if (event.key.code == sf::Keyboard::Up){
            current_block.rotate();
            game.get_grid().clean_grid();
            game.get_grid().display_block(current_block);
            game.get_grid().display_grid();
        }
    }

    if(event.type == sf::Event::KeyReleased)
        if (event.key.code == sf::Keyboard::Down)
            game.set_fps_grid(1);
    //Ajouter les actions que l'utilisateur peut realiser
};