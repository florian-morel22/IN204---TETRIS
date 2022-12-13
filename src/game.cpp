#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../inc/game.hpp"
#include "types_block/block_I.hpp"
#include "types_block/block_T.hpp"

void Game::Run(){
    while (_running)
        Frame();
}

Game::Game()
{
    printf("Initialisation\n");
    window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "TETRIS", sf::Style::Close);
    window.setVerticalSyncEnabled(true); // Optimisation de la fenetre

    // Création de 2 vues côtes a côte : a gauche la grille, a droite le menu
    grid_view.setViewport(sf::FloatRect(0.f, 0.f, 0.7f, 1.f));
    menu_view.setViewport(sf::FloatRect(0.7f, 0.f, 0.3f, 1.f));
    pop_up_view.setViewport(sf::FloatRect(0.2f, 0.3f, 0.6f, 0.4f));
    printf("getsize : %f, %f\n", grid_view.getSize().x, grid_view.getSize().y);

    bgGrid_.setSize(grid_view.getSize());
    bgGrid_.setFillColor(sf::Color(238, 238, 238));
    bgMenu_.setSize(menu_view.getSize());
    bgMenu_.setFillColor(sf::Color::Green);
    bgPopUp_.setSize(pop_up_view.getSize());
    bgPopUp_.setFillColor(sf::Color::White);

    // Création et initialisation de la grille
    try{
        grid.initialize_grid(10, 20, grid_view.getSize());
    }
    catch(std::exception const& e){
        printf("erreur : %s\n", e.what());
        _running=false;
        return;
    }

    // Création du frame rate
    fps_grid = 1;

    if (!main_font_.loadFromFile("../fonts/Berliner_Wand.ttf"))
    {
        printf("error of Berliner_Wand loading\n");
    }
    end_msg_.setFont(main_font_);
    end_msg_.setString("Perdu !!");
    end_msg_.setCharacterSize(100);
    end_msg_.setFillColor(sf::Color::Blue);
    sf::Vector2f center {pop_up_view.getSize().x/2,pop_up_view.getSize().y/2};
    setTextCenterPosition(end_msg_, center);

    //permet de créer des nombres aléatoires par la suite
    std::srand((unsigned) time(NULL));

    generate_new_block();
    current_block->display_block(grid);
    grid.display_grid();
}


Game::~Game(){
    try{
        grid.Free_grid<int**>(grid.get_grid_num(), grid.get_size().x+4);
        grid.Free_grid<sf::RectangleShape**>(grid.get_grid_drawn(), grid.get_size().x);
    }
    catch(std::exception &e){
        //printf("erreur : %s\n", e.what());
        printf("erreur : %s\n", e.what());
    }
    delete current_block; // => core dumped ?????????????????????
    window.close();
    printf("Fermeture\n");
}

void Game::Frame()
{

    // Gestion de des events utilisateurs
    sf::Event event;
    while (window.pollEvent(event))
    {
        InputHandler(event, *this, *current_block, grid);
    }

    // On affiche tout !

    if(!_game_break && clock.getElapsedTime().asMilliseconds() > (1000 / fps_grid))
    {

        current_block->hide_block(grid);

        if(!current_block->go_down(grid)){
            integrate_block_to_grid();
            if(!generate_new_block())_game_break = !_game_break;
        }
           


        current_block->display_block(grid);
        grid.display_grid();

        clock.restart();
    }

    window.clear();

    window.setView(grid_view);
    window.draw(bgGrid_);

    // a suppr
    grid.draw_grid();
    for (int i = 0; i < grid.get_size().x; i++)
    {
        for (int j = 0; j < grid.get_size().y; j++)
        {
            window.draw(grid.get_case_value_drawn(i, j));
        }
    }

    window.setView(menu_view);
    window.draw(bgMenu_);

    if(_game_break){
        window.setView(pop_up_view);
        window.draw(bgPopUp_);
        window.draw(end_msg_);
    }

    window.display();
}

void Game::set_running(bool new_running)
{
    _running = new_running;
}

void Game::set_fps_grid(float new_fps_grid)
{
    fps_grid = new_fps_grid;
}

void Game::set_game_break()
{
    _game_break = !_game_break;
};

Grid Game::get_grid() const
{
    return grid;
}

void Game::integrate_block_to_grid()
{
    // On incorpore le block à la grid avant d'en creer un nouveau.

    for (size_t k = 0; k < current_block->get_list_squares().size(); k++){
        int i_ = current_block->get_list_squares()[k].x;
        int j_ = current_block->get_list_squares()[k].y;
        grid.set_case_value(i_, j_, current_block->get_value());
    }
}

bool Game::generate_new_block()
{
    //enum Block {I, J, L, O, S, Z, T};
    int value_new_block = 1+(std::rand()%8);

    switch (value_new_block){
        case 1:
            current_block = new Block_I(6, 2);
            break;
        case 2:
            current_block = new Block_J(6, 3);
            break;
        case 3:
            current_block = new Block_L(6, 3);
            break;
        case 4:
            current_block = new Block_O(6, 2);
            break;
        case 5:
            current_block = new Block_S(5, 2);
            break;
        case 6:
            current_block = new Block_Z(5, 2);
            break;
        default:
            current_block = new Block_T(6, 3);
    }

    // Condition for the end of the game
    for(size_t k=0;k<current_block->get_list_squares().size();k++)
    {
        int i_ = current_block->get_list_squares()[k].x;
        int j_ = current_block->get_list_squares()[k].y;
        if(grid.get_case_value(i_, j_)!=0) {
            return false;
        }
    }
    return true;
}

void InputHandler(sf::Event event, Game &game, Block &current_block, Grid &grid /*, sf::RenderWindow& window*/)
{

    if (event.type == sf::Event::Closed)
        game.set_running(false);
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Down)
            game.set_fps_grid(20);
        if (event.key.code == sf::Keyboard::Right)
        {
            current_block.hide_block(grid);
            current_block.go_right(grid);
            current_block.display_block(grid);
        }
        if (event.key.code == sf::Keyboard::Left)
        {
            current_block.hide_block(grid);
            current_block.go_left(grid);
            current_block.display_block(grid);
        }
        if (event.key.code == sf::Keyboard::Up)
        {
            current_block.hide_block(grid);
            current_block.rotate(grid);
            current_block.display_block(grid);
        }
    }

    if (event.type == sf::Event::KeyReleased)
        if (event.key.code == sf::Keyboard::Down)
            game.set_fps_grid(1);
    // Ajouter les actions que l'utilisateur peut realiser
};