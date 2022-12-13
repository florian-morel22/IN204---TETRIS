#ifndef GAME_HPP
# define GAME_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "grid.hpp"
#include "block.hpp"
#include "./types_block/block_I.hpp"
#include "./types_block/block_L.hpp"
#include "./types_block/block_J.hpp"
#include "./types_block/block_O.hpp"
#include "./types_block/block_S.hpp"
#include "./types_block/block_Z.hpp"
#include "./types_block/block_T.hpp"
#include "utils.hpp"

namespace tetris {


const int WIN_WIDTH = 1500;
const int WIN_HEIGHT = 1000;
const std::string MY_PATH = "/home/IN204/project";


class Game
{
     public:
        void Run();

        Game();
        ~Game();

        void set_running(bool new_running);
        void set_fps_grid(float new_fps_grid);
        void set_game_break();
      
        Grid get_grid()const;

        void integrate_block_to_grid();
        bool generate_new_block();

    private:

        bool _running = true;
        bool _game_break = false;

        sf::RenderWindow window;
        sf::View grid_view;
        sf::View menu_view;
        sf::View pop_up_view;


        sf::RectangleShape bgGrid_;
        sf::RectangleShape bgMenu_;
        sf::RectangleShape bgPopUp_;

        sf::Font main_font_;
        sf::Text end_msg_;

        Grid grid;

        Block *current_block;

        sf::Clock clock;
        float fps_grid;

        void Frame();

};

void InputHandler(sf::Event, Game &, Block &, Grid &);


} // !namespace tetris

#endif // !GAME_HPP
