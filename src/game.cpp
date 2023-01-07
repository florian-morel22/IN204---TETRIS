#include "../inc/game.hpp"
#include "utils.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>

namespace tetris {

void Game::Run() {
  while (_running)
    Frame();
}

Game::Game() {

  window.create(sf::VideoMode(WIN_WIDTH * 0.1, WIN_HEIGHT * 0.1), "TETRIS",
                sf::Style::Close);
  window.setVerticalSyncEnabled(true); // Window optimization
  WindowView.reset(sf::FloatRect(0, 0, WIN_WIDTH, WIN_HEIGHT));
  window.setView(WindowView);

  /* Grid creation and initilisation */

  grid.set_color_empty_block(sf::Color::Black);
  little_grid.set_color_empty_block(sf::Color(0, 0, 0, 0));

  try {
    grid.initialize_grid(10, 20,
                         {WIN_WIDTH - 4 * e - 2 * L_cases, WIN_HEIGHT - 2 * e},
                         {2 * e + L_cases, e});
  } catch (std::exception const &e) {
    printf("erreur : %s\n", e.what());
    _running = false;
    return;
  }

  try {
    little_grid.initialize_grid(
        4, 3, {L_cases * 0.4f, H_12 * 0.7f},
        {e + L_cases / 2 - L_cases * 0.2f, 0.2f * H_12});
  } catch (std::exception const &e) {
    printf("erreur : %s\n", e.what());
    _running = false;
    return;
  }

  // initialisation to use random numbers later
  std::srand((unsigned int)time(nullptr));

  Initialize_graphics();
  Initialize_game();

  std::string new_pseudo;
  std::cout << "Donnez votre pseudo : ";
  std::cin >> new_pseudo;
  player.set_pseudo(new_pseudo);
}

Game::~Game() {
  try {
    grid.Call_Free_grid("grid_num");
    grid.Call_Free_grid("grid_drawn");
    little_grid.Call_Free_grid("grid_num");
    little_grid.Call_Free_grid("grid_drawn");
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

  // user event management
  sf::Event event;
  while (window.pollEvent(event)) {
    InputHandler(event);
  }

  // We display everything
  if (go_to_next_gameFrame) {
    current_block->hide_block(grid);
    if (!current_block->go_down(grid)) {
      integrate_block_to_grid();
      points = grid.clean_full_lines(current_block->get_list_squares());
      if (points > 0) {
        player.add_score(points);
        network.sendInfosToHost(player);
      }
      current_block = next_block;
      generate_new_next_block();
      if (is_end_game())
        end_game = !end_game;
    }
    current_block->display_block(grid);
    little_grid.clean_grid();
    next_block->display_block(little_grid, -3, 0);

    clock.restart();
  }

  window.clear();

  window.draw(bgSprite);

  for (auto const &line : list_lines_rect) {
    window.draw(line);
  }
  for (auto const &line : list_lines_conv) {
    window.draw(line);
  }

  window.draw(Nexts_);
  window.draw(Multiplayers_);
  window.draw(Score_);

  // to delete ??
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

  little_grid.draw_grid();
  for (int i = 0; i < little_grid.get_size().x; i++) {
    for (int j = 0; j < little_grid.get_size().y; j++) {
      window.draw(little_grid.get_case_value_drawn(i, j));
    }
  }

  window.display();

  network.getInfosFromOtherPlayers(player);
}

void Game::set_running(bool new_running) { _running = new_running; }

void Game::set_fps_grid(float new_fps_grid) { fps_grid = new_fps_grid; }

void Game::set_game_break() { end_game = !end_game; }

Grid Game::get_grid() const { return grid; }

void Game::integrate_block_to_grid() {
  // Adding the block in the grid before generating a new one

  for (size_t k = 0; k < current_block->get_list_squares().size(); k++) {
    int i_ = current_block->get_list_squares()[k].x;
    int j_ = current_block->get_list_squares()[k].y;
    grid.set_case_value(i_, j_, current_block->get_value());
  }
}

void Game::generate_new_next_block() {
  enum Block { I = 1, J, L, O, S, Z, T };
  int value_new_block = 1 + (std::rand() % 8);

  switch (value_new_block) {
  case I:
    next_block = new Block_I(5, 3);
    break;
  case J:
    next_block = new Block_J(6, 3);
    break;
  case L:
    next_block = new Block_L(6, 3);
    break;
  case O:
    next_block = new Block_O(6, 2);
    break;
  case S:
    next_block = new Block_S(5, 2);
    break;
  case Z:
    next_block = new Block_Z(5, 2);
    break;
  default:
    next_block = new Block_T(6, 3);
  }
}

bool Game::is_end_game() {
  // End game condition
  for (size_t k = 0; k < current_block->get_list_squares().size(); k++) {
    int i_ = current_block->get_list_squares()[k].x;
    int j_ = current_block->get_list_squares()[k].y;
    if (grid.get_case_value(i_, j_) != 0) {
      return true;
    }
  }
  return false;
};

void Game::Initialize_game() {
  fps_grid = 1;
  player.set_score(0);

  grid.clean_grid_with_borders();
  grid.clean_grid();
  little_grid.clean_grid_with_borders();
  little_grid.clean_grid();

  generate_new_next_block();
  current_block = next_block;
  generate_new_next_block();
  current_block->display_block(grid);
  next_block->display_block(little_grid, -3, 0);

  clock.restart();
}

void Game::Initialize_graphics() {

  /* ---------- INITIALISATION OF TEXTS ---------- */

  float H_Text_Suivants_Multijoueurs = 1.5 * e;
  sf::Color title_cases_color = sf::Color(255, 222, 89);

  if (!main_font_.loadFromFile(MY_PATH +
                               "/repository/fonts/BigShouldersDisplay.ttf")) {
    printf("error of Berliner_Wand loading\n");
  }
  initialize_text(end_msg_, main_font_, 1, WindowView.getCenter(),
                  0.2 * (WIN_WIDTH - 4 * e - 2 * L_cases), "TERMINADO",
                  sf::Color::White, {1, 0.7});
  initialize_text(try_again_, main_font_, 1,
                  {WindowView.getCenter().x, WindowView.getCenter().y * 5 / 4},
                  0.1 * (WIN_WIDTH - 4 * e - 2 * L_cases), "Click to try again",
                  sf::Color::White, {1, 0.7});
  initialize_text(Nexts_, main_font_, 2,
                  {e + L_cases / 2, H_Text_Suivants_Multijoueurs},
                  0.2 * L_cases, "SUIVANTS", title_cases_color, {1, 0.7});
  initialize_text(Multiplayers_, main_font_, 2,
                  {WIN_WIDTH - e - L_cases / 2, H_Text_Suivants_Multijoueurs},
                  0.2 * L_cases, "MULTIJOUEURS", title_cases_color, {1, 0.7});
  initialize_text(
      Score_, main_font_, 3,
      {e + L_cases / 2, WIN_HEIGHT - H_Text_Suivants_Multijoueurs - 0.2f * e},
      0.2 * L_cases, "SCORE", title_cases_color, {1, 0.7});

  /* ---------- INITIALISATION OF BACKGROUNDS ---------- */

  float blurGrid_Opacity = 180; // 180/255

  if (!bgTexture.loadFromFile(MY_PATH + "/repository/images/background.png")) {
    // error...
  }
  bgSprite.setTexture(bgTexture);
  scaleToMinSize(bgSprite, WIN_HEIGHT, WIN_WIDTH);

  blurGrid_.setPosition({2 * e + L_cases, e});
  blurGrid_.setSize({WIN_WIDTH - 4 * e - 2 * L_cases, WIN_HEIGHT - 2 * e});
  blurGrid_.setFillColor(sf::Color(0, 0, 0, blurGrid_Opacity));

  /* ---------- INITIALISATION OF LINES ---------- */

  sf::Color ColorBorder = sf::Color(203, 108, 230);

  sf::RectangleShape line11(sf::Vector2f(L_cases, thickness));
  sf::RectangleShape line12(sf::Vector2f(H_12, thickness));
  sf::RectangleShape line13(sf::Vector2f(H_13, thickness));
  sf::ConvexShape line14;

  line11.setFillColor(ColorBorder);
  line11.setPosition(e, e);

  line12.rotate(90.f);
  line12.setFillColor(ColorBorder);
  line12.setPosition(e + thickness, e);

  line13.rotate(90.f);
  line13.setFillColor(ColorBorder);
  line13.setPosition(e + L_cases, e);

  line14.setPointCount(4);
  line14.setPoint(0, sf::Vector2f(e, e + H_12));
  line14.setPoint(1, sf::Vector2f(e, e + H_12 + thickness));
  line14.setPoint(2, sf::Vector2f(e + L_cases, e + H_13));
  line14.setPoint(3, sf::Vector2f(e + L_cases, e + H_13 - thickness));
  line14.setFillColor(ColorBorder);

  sf::RectangleShape line21(sf::Vector2f(L_cases, thickness));
  sf::RectangleShape line22(sf::Vector2f(H_22, thickness));
  sf::RectangleShape line23(sf::Vector2f(H_23, thickness));
  sf::ConvexShape line24;

  line21.setFillColor(ColorBorder);
  line21.setPosition(e, WIN_HEIGHT - e - thickness);

  line22.rotate(90.f);
  line22.setFillColor(ColorBorder);
  line22.setPosition(e + thickness, WIN_HEIGHT - H_22 - e);

  line23.rotate(90.f);
  line23.setFillColor(ColorBorder);
  line23.setPosition(e + L_cases, WIN_HEIGHT - H_23 - e);

  line24.setPointCount(4);
  line24.setPoint(0, sf::Vector2f(e, WIN_HEIGHT - e - H_22));
  line24.setPoint(1, sf::Vector2f(e, WIN_HEIGHT - e - H_22 + thickness));
  line24.setPoint(2, sf::Vector2f(e + L_cases, WIN_HEIGHT - H_23 - e));
  line24.setPoint(3,
                  sf::Vector2f(e + L_cases, WIN_HEIGHT - H_23 - e - thickness));
  line24.setFillColor(ColorBorder);

  sf::RectangleShape line31(sf::Vector2f(L_cases, thickness));
  sf::RectangleShape line32(sf::Vector2f(H_32, thickness));
  sf::RectangleShape line33(sf::Vector2f(H_33, thickness));
  sf::ConvexShape line34;

  line31.setFillColor(ColorBorder);
  line31.setPosition(WIN_WIDTH - e - L_cases, e);

  line32.rotate(90.f);
  line32.setFillColor(ColorBorder);
  line32.setPosition(WIN_WIDTH - e - L_cases + thickness, e);

  line33.rotate(90.f);
  line33.setFillColor(ColorBorder);
  line33.setPosition(WIN_WIDTH - e, e);

  line34.setPointCount(4);
  line34.setPoint(0, sf::Vector2f(WIN_WIDTH - e - L_cases, e + H_32));
  line34.setPoint(1,
                  sf::Vector2f(WIN_WIDTH - e - L_cases, e + H_32 + thickness));
  line34.setPoint(2, sf::Vector2f(WIN_WIDTH - e, e + H_33));
  line34.setPoint(3, sf::Vector2f(WIN_WIDTH - e, e + H_33 - thickness));
  line34.setFillColor(ColorBorder);

  sf::RectangleShape line41(sf::Vector2f(L_cases, thickness));
  sf::RectangleShape line42(sf::Vector2f(H_42, thickness));
  sf::RectangleShape line43(sf::Vector2f(H_43, thickness));
  sf::ConvexShape line44;

  line41.setFillColor(ColorBorder);
  line41.setPosition(WIN_WIDTH - e - L_cases, WIN_HEIGHT - e - thickness);

  line42.rotate(90.f);
  line42.setFillColor(ColorBorder);
  line42.setPosition(WIN_WIDTH - e - L_cases + thickness,
                     WIN_HEIGHT - e - H_42);

  line43.rotate(90.f);
  line43.setFillColor(ColorBorder);
  line43.setPosition(WIN_WIDTH - e, WIN_HEIGHT - H_43 - e);

  line44.setPointCount(4);
  line44.setPoint(0,
                  sf::Vector2f(WIN_WIDTH - e - L_cases, WIN_HEIGHT - e - H_42));
  line44.setPoint(1, sf::Vector2f(WIN_WIDTH - e - L_cases,
                                  WIN_HEIGHT - e - H_42 + thickness));
  line44.setPoint(2, sf::Vector2f(WIN_WIDTH - e, WIN_HEIGHT - H_43 - e));
  line44.setPoint(
      3, sf::Vector2f(WIN_WIDTH - e, WIN_HEIGHT - H_43 - e - thickness));
  line44.setFillColor(ColorBorder);

  list_lines_rect.push_back(line11);
  list_lines_rect.push_back(line12);
  list_lines_rect.push_back(line13);
  list_lines_rect.push_back(line21);
  list_lines_rect.push_back(line22);
  list_lines_rect.push_back(line23);
  list_lines_rect.push_back(line31);
  list_lines_rect.push_back(line32);
  list_lines_rect.push_back(line33);
  list_lines_rect.push_back(line41);
  list_lines_rect.push_back(line42);
  list_lines_rect.push_back(line43);
  list_lines_conv.push_back(line14);
  list_lines_conv.push_back(line24);
  list_lines_conv.push_back(line34);
  list_lines_conv.push_back(line44);
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
    if (event.key.code == sf::Keyboard::H) {
      if (!player.isClient() && !player.isHost()) {
        player.set_Host(true);
        std::string new_port_string;
        std::cout << "choisir un port : ";
        std::cin >> new_port_string;

        unsigned short new_port =
            (unsigned short)std::stoul(new_port_string, nullptr, 0);
        network.set_port(new_port);

        network.runHost();

        printf("Vous avez créé un serveur host, vous devez vous y connecté en "
               "utilisant la touche C.\n");
      }
    }
    if (event.key.code == sf::Keyboard::C) {
      if (!player.isClient()) {
        unsigned short port;
        std::string ip_string;

        /*std::cout << "Adresse ip du serveur : ";
        std::cin >> ip_string;*/
        std::cout << "port : ";
        std::cin >> port;

        // sf::IpAddress ip(ip_string);

        sf::IpAddress ip = network.get_ip();
        // unsigned short port = network.get_port();

        network.connectAsClient(ip, port, player);
      }
    }
    if (event.key.code == sf::Keyboard::Q) {
      if (player.isHost()) {
        network.stop_Host();
        // if success :
        player.set_Host(false);
        player.set_Client(false);
      }
    }
  }

  if (event.type == sf::Event::KeyReleased)
    if (!end_game && event.key.code == sf::Keyboard::Down)
      set_fps_grid(1);

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    if (localPosition.x * 10 > (2 * e + L_cases) &&
        localPosition.x * 10 < (WIN_WIDTH - 2 * e - L_cases) && end_game) {
      Initialize_game();
      end_game = !end_game;
    }
  }
};

} // namespace tetris