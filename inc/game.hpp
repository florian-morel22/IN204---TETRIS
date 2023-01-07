#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "./types_block/block_I.hpp"
#include "./types_block/block_J.hpp"
#include "./types_block/block_L.hpp"
#include "./types_block/block_O.hpp"
#include "./types_block/block_S.hpp"
#include "./types_block/block_T.hpp"
#include "./types_block/block_Z.hpp"
#include "block.hpp"
#include "grid.hpp"
#include "network.hpp"
#include "utils.hpp"

namespace tetris {

class Game {
private:
  bool _running = true;
  bool end_game = false;

  int score = 0;
  int points = 0;

  sf::RenderWindow window;
  sf::View WindowView;

  std::vector<sf::RectangleShape> list_lines_rect;
  std::vector<sf::ConvexShape> list_lines_conv;

  sf::Sprite bgSprite;
  sf::Texture bgTexture;
  sf::Color ColorBorder;

  sf::RectangleShape blurGrid_;

  sf::Font main_font_;
  sf::Text end_msg_;
  sf::Text try_again_;
  sf::Text Nexts_;
  sf::Text Multiplayers_;
  sf::Text Score_;

  Grid grid;
  Grid little_grid;

  Block *current_block;
  Block *next_block;

  sf::Clock clock;
  float fps_grid;

  Player player;

  Network network;

  void Frame();
  void InputHandler(sf::Event);
  void Initialize_game();
  void Initialize_graphics();

public:
  Game();
  ~Game();
  void Run();

  void set_running(bool new_running);
  void set_fps_grid(float new_fps_grid);
  void set_game_break();

  Grid get_grid() const;

  void integrate_block_to_grid();
  void generate_new_next_block();
  bool is_end_game();
};

void InputHandler(sf::Event, Game &, Block &, Grid &);

} // namespace tetris

#endif // !GAME_HPP
