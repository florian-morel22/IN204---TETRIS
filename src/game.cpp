#include "../inc/game.hpp"
#include "utils.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

namespace tetris {

void Game::Run() {
  while (_running)
    Frame();
}

Game::Game() {
  printf("Initialisation\n");

  /*Scaling different views*/
  float grid_view_x = 0;
  float grid_view_y = 0;
  float grid_view_dx = 0.5;
  float grid_view_dy = 1;

  float menu_view_x = grid_view_x + grid_view_dx;
  float menu_view_y = grid_view_y;
  float menu_view_dx = 1 - grid_view_dx;
  float menu_view_dy = grid_view_dy;

  sf::FloatRect scale_grid_view = {grid_view_x, grid_view_y, grid_view_dx,
                                   grid_view_dy};
  sf::FloatRect scale_menu_view = {menu_view_x, menu_view_y, menu_view_dx,
                                   menu_view_dy};
  /* END Scaling different views*/

  window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "TETRIS",
                sf::Style::Close);
  window.setVerticalSyncEnabled(true); // Optimisation de la fenetre

  // Création de 2 vues côtes a côte : a gauche la grille, a droite le menu
  grid_view.setViewport(scale_grid_view);
  menu_view.setViewport(scale_menu_view);

  bgGrid_.setSize(grid_view.getSize());
  bgGrid_.setFillColor(sf::Color(238, 238, 238));
  bgMenu_.setSize(menu_view.getSize());
  bgMenu_.setFillColor(sf::Color(255, 255, 255));

  blurGrid_.setSize(grid_view.getSize());
  blurGrid_.setFillColor(sf::Color(192, 192, 192, 150));

  // Création et initialisation de la grille
  try {
    grid.initialize_grid(10, 20, grid_view.getSize());
  } catch (std::exception const &e) {
    printf("erreur : %s\n", e.what());
    _running = false;
    return;
  }

  if (!main_font_.loadFromFile(
          "/home/ensta/IN204/project/repository/fonts/Berliner_Wand.ttf")) {
    printf("error of Berliner_Wand loading\n");
  }
  initialize_text(end_msg_, main_font_, grid_view.getCenter(), 100, "TERMINADO",
                  sf::Color(34, 19, 73), {1, 0.7});
  initialize_text(try_again_, main_font_,
                  {grid_view.getCenter().x, grid_view.getCenter().y * 5 / 4},
                  50, "Click to try again", sf::Color(34, 19, 73), {1, 0.7});

  // permet de créer des nombres aléatoires par la suite
  std::srand((unsigned int)time(nullptr));

  Initialize_game();
}

Game::~Game() {
  try {
    grid.Call_Free_grid("grid_num");
    grid.Call_Free_grid("grid_drawn");
  } catch (std::exception &e) {
    printf("erreur : %s\n", e.what());
  }
  // delete current_block; // => core dumped ?????????????????????
  window.close();
  printf("Fermeture\n");
}

void Game::Frame() {

  bool go_to_next_gameFrame =
      !end_game && clock.getElapsedTime().asMilliseconds() > (1000 / fps_grid);
  bool display_try_again =
      end_game && clock.getElapsedTime().asMilliseconds() > 500;
  bool hide_try_again =
      end_game && clock.getElapsedTime().asMilliseconds() > 1000;

  // Gestion de des events utilisateurs
  sf::Event event;
  while (window.pollEvent(event)) {
    InputHandler(event);
  }

  // On affiche tout !

  if (go_to_next_gameFrame) {
    current_block->hide_block(grid);
    if (!current_block->go_down(grid)) {
      integrate_block_to_grid();
      if (!generate_new_block())
        end_game = !end_game;
    }
    current_block->display_block(grid);
    // grid.display_grid();

    clock.restart();
  }

  window.clear();

  window.setView(grid_view);
  window.draw(bgGrid_);

  // a suppr
  grid.draw_grid();
  for (int i = 0; i < grid.get_size().x; i++) {
    for (int j = 0; j < grid.get_size().y; j++) {
      window.draw(grid.get_case_value_drawn(i, j));
    }
  }

  if (end_game) {
    window.draw(blurGrid_);
    window.draw(end_msg_);
    if (display_try_again) {
      window.draw(try_again_);
      if (hide_try_again)
        clock.restart();
    }
  }

  window.setView(menu_view);
  window.draw(bgMenu_);

  window.display();
}

void Game::set_running(bool new_running) { _running = new_running; }

void Game::set_fps_grid(float new_fps_grid) { fps_grid = new_fps_grid; }

void Game::set_game_break() { end_game = !end_game; }

Grid Game::get_grid() const { return grid; }

void Game::integrate_block_to_grid() {
  // On incorpore le block à la grid avant d'en creer un nouveau.

  for (size_t k = 0; k < current_block->get_list_squares().size(); k++) {
    int i_ = current_block->get_list_squares()[k].x;
    int j_ = current_block->get_list_squares()[k].y;
    grid.set_case_value(i_, j_, current_block->get_value());
  }
}

bool Game::generate_new_block() {
  // enum Block {I, J, L, O, S, Z, T};
  int value_new_block = 1 + (std::rand() % 8);

  switch (value_new_block) {
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
  for (size_t k = 0; k < current_block->get_list_squares().size(); k++) {
    int i_ = current_block->get_list_squares()[k].x;
    int j_ = current_block->get_list_squares()[k].y;
    if (grid.get_case_value(i_, j_) != 0) {
      return false;
    }
  }
  return true;
}

void Game::Initialize_game() {
  fps_grid = 1;

  grid.clean_grid_with_borders();
  grid.clean_grid();

  generate_new_block();
  current_block->display_block(grid);

  clock.restart();
}

void Game::InputHandler(sf::Event event) {

  if (event.type == sf::Event::Closed)
    set_running(false);
  if (event.type == sf::Event::KeyPressed) {
    if (!end_game && event.key.code == sf::Keyboard::Down)
      set_fps_grid(50);
    if (!end_game && event.key.code == sf::Keyboard::Right) {
      current_block->hide_block(grid);
      current_block->go_right(grid);
      current_block->display_block(grid);
    }
    if (!end_game && event.key.code == sf::Keyboard::Left) {
      current_block->hide_block(grid);
      current_block->go_left(grid);
      current_block->display_block(grid);
    }
    if (!end_game && event.key.code == sf::Keyboard::Up) {
      current_block->hide_block(grid);
      current_block->rotate(grid);
      current_block->display_block(grid);
    }
  }

  if (event.type == sf::Event::KeyReleased)
    if (!end_game && event.key.code == sf::Keyboard::Down)
      set_fps_grid(1);

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    if (localPosition.x < 0.5 * WIN_WIDTH && end_game) {
      Initialize_game();
      end_game = !end_game;
    }
  }
};

} // namespace tetris