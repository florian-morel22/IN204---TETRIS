#include <cstddef>
#include <cstdio>
#include <exception>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>


#include "../inc/game.hpp"



void Game::Run(){
    Initialize();
    while (_running)
        Frame();
    Shutdown();
}

void Game::Initialize()
{
    printf("Initialisation\n");
    window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "TETRIS", sf::Style::Close);
    window.setVerticalSyncEnabled(true); // Optimisation de la fenetre

    // Création de 2 vues côtes a côte : a gauche la grille, a droite le menu
    grid_view.setViewport(sf::FloatRect(0.f, 0.f, 0.7f, 1.f));
    menu_view.setViewport(sf::FloatRect(0.7f, 0.f, 0.3f, 1.f));

    bgGrid_.setSize(grid_view.getSize());
    bgGrid_.setFillColor(sf::Color(238, 238, 238));
    bgMenu_.setSize(menu_view.getSize());
    bgMenu_.setFillColor(sf::Color::Green);

    // Création et initialisation de la grille
    try{
        grid.initialize_grid(10, 20);
    }
    catch(std::exception const& e){
        printf("erreur : %s\n", e.what());
        _running=false;
        return;
    }

    // Création du frame rate
    fps_grid = 1;

    //permet de créer des nombres aléatoires par la suite
    std::srand((unsigned) time(NULL));

    current_block = new Block_T(5,3);
    current_block->display_block(grid);
    grid.display_grid();
}


void Game::Shutdown(){
    try{
        grid.Free_grid<unsigned int**>(grid.get_grid_num(), grid.get_size().x+4);
        grid.Free_grid<sf::RectangleShape**>(grid.get_grid_drawn(), grid.get_size().x);
    }
    catch(std::exception &e){
        //printf("erreur : %s\n", e.what());
        printf("erreur : %s\n", e.what());
    }
    //delete[] current_block; // => core dumped ?????????????????????
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

    if (clock.getElapsedTime().asMilliseconds() > (1000 / fps_grid))
    {

        current_block->hide_block(grid);

        if (!current_block->go_down(grid))
            generate_new_block();

        current_block->display_block(grid);
        grid.display_grid();

        clock.restart();
    }

    window.clear();

    window.setView(grid_view);
    window.draw(bgGrid_);

    // a suppr
    grid.draw_grid();
    for (unsigned int i = 0; i < grid.get_size().x; i++)
    {
        for (unsigned int j = 0; j < grid.get_size().y; j++)
        {
            window.draw(grid.get_case_value_drawn(i, j));
        }
    }

    window.setView(menu_view);
    window.draw(bgMenu_);

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

Grid Game::get_grid() const
{
    return grid;
}

void Game::generate_new_block()
{

    // On incorpore le block à la grid avant d'en creer un nouveau.
    for (size_t k = 0; k < current_block->get_list_squares().size(); k++)
    {
        unsigned int i_ = current_block->get_list_squares()[k].x;
        unsigned int j_ = current_block->get_list_squares()[k].y;
        grid.set_case_value(i_, j_, current_block->get_value());
    }

    int value_new_block = 1+(std::rand()%7);
    
    if (value_new_block==1)
        current_block = new Block_I(4, 2);
    else if (value_new_block == 2)
        current_block = new Block_J(4, 2);
    else if (value_new_block == 3)
        current_block = new Block_L(4, 2);
    else if (value_new_block == 4)
        current_block = new Block_O(4, 2);
    else if (value_new_block == 5)
        current_block = new Block_S(4, 2);
    else
        current_block = new Block_Z(4, 2);
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