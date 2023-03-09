#include "../inc/game.hpp"
#include "../inc/player.hpp"
#include "../inc/utils.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <string>
#include <vector>

namespace tetris {

void Game::Run() {
  while (_running)
    if (screen == 1)
      HomeScreen();
    else if (screen == 2)
      MultiPlayerScreen();
    else if (screen == 3)
      WaitingScreen();
    else if (screen == 4)
      QuittingScreen();
    else
      GameScreen();
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

  // initialization to use random numbers later
  std::srand((unsigned int)time(nullptr));

  Initialize_graphics();
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
  if (player.isHost()) {
    network.sendDataToHost(player, "server down");
  }

  window.close();
  printf("Fermeture\n");
}

void Game::HomeScreen() {

  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      set_running(false);

    if (event.type == sf::Event::TextEntered) {

      if (event.text.unicode == 8 && playerInput.length() > 0) {
        playerInput.pop_back();
        playerText.setString(playerInput);
      }

      else if (event.text.unicode > 96 && event.text.unicode < 123 &&
               playerInput.length() < 7) {
        playerInput += event.text.unicode;
        playerText.setString(playerInput);
      }

      float offset_x = playerText.getPosition().x -
                       playerText.getGlobalBounds().left -
                       playerText.getGlobalBounds().width / 2.;
      playerText.setPosition(
          sf::Vector2f{WIN_WIDTH / 2.f + offset_x, playerText.getPosition().y});
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2i localPosition = sf::Mouse::getPosition(window);
      if (localPosition.x * 10 > soloButton.getPosition().x &&
          localPosition.x * 10 <
              soloButton.getPosition().x + soloButton.getSize().x &&
          localPosition.y * 10 > soloButton.getPosition().y &&
          localPosition.y * 10 <
              soloButton.getPosition().y + soloButton.getSize().y)

      {
        if (playerInput.length() > 0) {
          player.set_pseudo(playerInput);
          Initialize_game();
          screen = 0;
        }
      }
      if (localPosition.x * 10 > multiButton.getPosition().x &&
          localPosition.x * 10 <
              multiButton.getPosition().x + multiButton.getSize().x &&
          localPosition.y * 10 > multiButton.getPosition().y &&
          localPosition.y * 10 <
              multiButton.getPosition().y + multiButton.getSize().y)

      {
        if (playerInput.length() > 0) {
          player.set_pseudo(playerInput);
          screen = 2;

          // To avoid a double click with a bad sensitivity of the mouse
          std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
      }
    }
  }

  window.clear();
  window.draw(bgSprite);
  window.draw(Title_game);
  window.draw(pickYourName);
  window.draw(playerText);
  window.draw(soloButton);
  window.draw(Solo_Button_);
  window.draw(multiButton);
  window.draw(Multi_Button_);
  window.draw(pseudoBox);
  window.display();
}

void Game::MultiPlayerScreen() {

  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      set_running(false);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2i localPosition = sf::Mouse::getPosition(window);
      if (localPosition.x * 10 > BackButton.getPosition().x &&
          localPosition.x * 10 <
              BackButton.getPosition().x + BackButton.getSize().x &&
          localPosition.y * 10 > BackButton.getPosition().y &&
          localPosition.y * 10 <
              BackButton.getPosition().y + BackButton.getSize().y) {
        screen = 1;

        // To avoid a double click with a bad sensitivity of the mouse
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
      if (localPosition.x * 10 > ClientButton.getPosition().x &&
          localPosition.x * 10 <
              ClientButton.getPosition().x + ClientButton.getSize().x &&
          localPosition.y * 10 > ClientButton.getPosition().y &&
          localPosition.y * 10 <
              ClientButton.getPosition().y + ClientButton.getSize().y &&
          HostButton_Selected) {

        ClientButton.setFillColor(sf::Color(203, 108, 230));
        HostButton.setFillColor(sf::Color::Transparent);

        ipString = "";
        portString = "";
        ipInput.setString(ipString);
        portInput.setString(portString);

        Create_.setString("Rejoindre");
        sf::Vector2f pos_PlayButton = {
            CreateButton.getPosition().x + CreateButton.getSize().x / 2,
            CreateButton.getPosition().y + CreateButton.getSize().y / 2};
        setTextCenterPosition(Create_, pos_PlayButton);

        ipBox.setOutlineThickness(WIN_WIDTH / 100.f);

        HostButton_Selected = false;
      }
      if (localPosition.x * 10 > HostButton.getPosition().x &&
          localPosition.x * 10 <
              HostButton.getPosition().x + HostButton.getSize().x &&
          localPosition.y * 10 > HostButton.getPosition().y &&
          localPosition.y * 10 <
              HostButton.getPosition().y + HostButton.getSize().y) {

        HostButton.setFillColor(sf::Color(203, 108, 230));
        ClientButton.setFillColor(sf::Color::Transparent);

        ipString = network.get_ip().toString();
        portString = std::to_string(network.get_port());
        ipInput.setString(ipString);
        portInput.setString(portString);

        Create_.setString("Creer");
        sf::Vector2f pos_PlayButton = {
            CreateButton.getPosition().x + CreateButton.getSize().x / 2,
            CreateButton.getPosition().y + CreateButton.getSize().y / 2};
        setTextCenterPosition(Create_, pos_PlayButton);

        ipBox.setOutlineThickness(WIN_WIDTH / 1000.f);
        portBox.setOutlineThickness(WIN_WIDTH / 1000.f);

        HostButton_Selected = true;
      }
      if (localPosition.x * 10 > ipBox.getPosition().x &&
          localPosition.x * 10 < ipBox.getPosition().x + ipBox.getSize().x &&
          localPosition.y * 10 > ipBox.getPosition().y &&
          localPosition.y * 10 < ipBox.getPosition().y + ipBox.getSize().y &&
          !HostButton_Selected) {

        ipBox.setOutlineThickness(WIN_WIDTH / 100.f);
        portBox.setOutlineThickness(WIN_WIDTH / 1000.f);

        ipBox_focused = true;
      }
      if (localPosition.x * 10 > portBox.getPosition().x &&
          localPosition.x * 10 <
              portBox.getPosition().x + portBox.getSize().x &&
          localPosition.y * 10 > portBox.getPosition().y &&
          localPosition.y * 10 <
              portBox.getPosition().y + portBox.getSize().y &&
          !HostButton_Selected) {

        ipBox.setOutlineThickness(WIN_WIDTH / 1000.f);
        portBox.setOutlineThickness(WIN_WIDTH / 100.f);

        ipBox_focused = false;
      }
      if (localPosition.x * 10 > CreateButton.getPosition().x &&
          localPosition.x * 10 <
              CreateButton.getPosition().x + CreateButton.getSize().x &&
          localPosition.y * 10 > CreateButton.getPosition().y &&
          localPosition.y * 10 <
              CreateButton.getPosition().y + CreateButton.getSize().y) {
        if (HostButton_Selected) {
          player.set_Host(true);
          network.runHost();

          std::this_thread::sleep_for(std::chrono::milliseconds(500));

          sf::IpAddress ip(ipString);
          unsigned short port =
              (unsigned short)std::stoul(portString, nullptr, 0);
          network.connectAsClient(ip, port, player);

          Play_.setString("Jouer");
          PlayButton.setPosition({WIN_WIDTH * 0.5f - PlayButton.getSize().x / 2,
                                  WIN_HEIGHT * 0.85f});

          sf::Vector2f pos_PlayButton = {
              PlayButton.getPosition().x + PlayButton.getSize().x / 2,
              PlayButton.getPosition().y + PlayButton.getSize().y / 2};
          setTextCenterPosition(Play_, pos_PlayButton);

          screen = 3;

        } else {
          sf::IpAddress ip(ipString);
          unsigned short port =
              (unsigned short)std::stoul(portString, nullptr, 0);
          network.connectAsClient(ip, port, player);

          screen = 3;
        }
      }
    }

    if (event.type == sf::Event::TextEntered && !HostButton_Selected) {
      if (ipBox_focused) {
        if (event.text.unicode == 8 && ipString.length() > 0) {
          ipString.pop_back();
          ipInput.setString(ipString);
        }

        else if (((event.text.unicode > 47 && event.text.unicode < 58) ||
                  event.text.unicode == 46) &&
                 ipString.length() < 15) {
          ipString += event.text.unicode;
          ipInput.setString(ipString);
        }
      } else {
        if (event.text.unicode == 8 && portString.length() > 0) {
          portString.pop_back();
          portInput.setString(portString);
        }

        else if (((event.text.unicode > 47 && event.text.unicode < 58) ||
                  event.text.unicode == 46) &&
                 portString.length() < 4) {
          portString += event.text.unicode;
          portInput.setString(portString);
        }
      }
    }
  }

  window.clear();
  window.draw(bgSprite);
  window.draw(HostButton);
  window.draw(ClientButton);
  window.draw(Create_server);
  window.draw(Join_server);
  window.draw(CreateButton);
  window.draw(BackButton);
  window.draw(GoBack_);
  window.draw(Create_);
  window.draw(ip_);
  window.draw(port_);
  window.draw(ipBox);
  window.draw(portBox);
  window.draw(ipInput);
  window.draw(portInput);

  window.display();
}

void Game::WaitingScreen() {

  sf::Event event;
  while (window.pollEvent(event)) {

    if (event.type == sf::Event::Closed)
      set_running(false);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2i localPosition = sf::Mouse::getPosition(window);
      if (player.isHost() &&
          localPosition.x * 10 > PlayButton.getPosition().x &&
          localPosition.x * 10 <
              PlayButton.getPosition().x + PlayButton.getSize().x &&
          localPosition.y * 10 > BackButton.getPosition().y &&
          localPosition.y * 10 <
              PlayButton.getPosition().y + PlayButton.getSize().y) {

        network.sendDataToHost(player, "play");
      }
    }

    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Q) {
        if (player.isHost()) {
          network.sendDataToHost(player, "server down");
          // if success :
          screen = 1;
          player.set_Host(false);
          player.set_Client(false);
        }
      }
    }
  }

  TypeDataFromHost = network.getDataFromHost(player, other_players);

  if (TypeDataFromHost == "add player to other_players") {
    sf::Text *pseudo_text = new sf::Text();
    sf::Text *score_text = new sf::Text();

    int n = pseudos_others_players.size();

    std::string pseudo_ = other_players[other_players.size() - 1]->get_pseudo();
    std::string score_ =
        std::to_string(other_players[other_players.size() - 1]->get_score());

    initialize_text(
        *pseudo_text, main_font_, 1,
        {WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.4f + n * 0.08f * WIN_HEIGHT},
        0.07f * WIN_HEIGHT, pseudo_, sf::Color::White, {1, 0.7});

    // This text is initialized for the next screen
    initialize_text(*score_text, main_font_, 6,
                    {WIN_WIDTH - e - thickness - 0.05f * L_cases,
                     e + thickness + (0.2f + 0.08f * n) * H_32},
                    0.15 * L_cases, score_, sf::Color::White, {1, 0.7});

    pseudos_others_players.push_back(pseudo_text);
    scores_others_players.push_back(score_text);
  }

  if (TypeDataFromHost == "play") {

    int n = 0;
    for (sf::Text *T : pseudos_others_players) {
      initialize_text(*T, main_font_, 5,
                      {WIN_WIDTH - e - 0.9f * L_cases,
                       e + thickness + (0.2f + 0.08f * n) * H_32},
                      0.15 * L_cases, T->getString(), sf::Color::White,
                      {1, 0.7});
      n += 1;
    }

    Initialize_game();
    screen = 0;
  }

  if (TypeDataFromHost == "server down") {
    Play_.setString("Fermer");
    sf::Vector2f pos_PlayButton = {
        PlayButton.getPosition().x + PlayButton.getSize().x / 2,
        PlayButton.getPosition().y + PlayButton.getSize().y / 2};
    setTextCenterPosition(Play_, pos_PlayButton);
    screen = 4;
  }

  window.clear();
  window.draw(bgSprite);
  window.draw(Title_waiting);

  if (player.isHost()) {
    window.draw(PlayButton);
    window.draw(Play_);
  }

  for (sf::Text *T : pseudos_others_players) {
    window.draw(*T);
  }
  window.display();
}

void Game::QuittingScreen() {
  sf::Event event;
  while (window.pollEvent(event)) {

    if (event.type == sf::Event::Closed)
      set_running(false);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2i localPosition = sf::Mouse::getPosition(window);
      if (localPosition.x * 10 > PlayButton.getPosition().x &&
          localPosition.x * 10 <
              PlayButton.getPosition().x + PlayButton.getSize().x &&
          localPosition.y * 10 > PlayButton.getPosition().y &&
          localPosition.y * 10 <
              PlayButton.getPosition().y + PlayButton.getSize().y) {

        set_running(false);
      }
    }
  }

  window.clear();
  window.draw(bgSprite);
  window.draw(PlayButton);
  window.draw(Quitting_);
  window.draw(Play_);
  window.display();
}

void Game::GameScreen() {

  bool go_to_next_gameFrame =
      !end_game && clock.getElapsedTime().asMilliseconds() > (1000 / fps_grid);
  bool display_try_again =
      end_game && clock.getElapsedTime().asMilliseconds() > 500;
  bool hide_try_again =
      end_game && clock.getElapsedTime().asMilliseconds() > 1000;

  sf::Vector2f middle_2nd_case = {e + L_cases / 2, WIN_HEIGHT - H_22 / 2};

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
        network.sendDataToHost(player, "update scores");
        player_score.setString(std::to_string(player.get_score()));
        setTextCenterPosition(player_score, middle_2nd_case);
      }
      current_block = next_block;
      generate_new_next_block();
      if (is_end_game()) {
        end_game = !end_game;
        if (player.isClient()) {
          screen = 3;
        }
      }
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
  window.draw(player_score);
  for (sf::Text *T : pseudos_others_players)
    window.draw(*T);
  for (sf::Text *T : scores_others_players)
    window.draw(*T);

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

  TypeDataFromHost = network.getDataFromHost(player, other_players);

  if (TypeDataFromHost == "update scores") {
    for (size_t k = 0; k < other_players.size(); k++) {
      scores_others_players[k]->setString(
          std::to_string(other_players[k]->get_score()));
      setTextRightCenterPosition(*scores_others_players[k],
                                 {WIN_WIDTH - e - thickness - 0.05f * L_cases,
                                  e + thickness + (0.2f + 0.08f * k) * H_32});
    }
  }
  if (TypeDataFromHost == "server down") {
    Play_.setString("Fermer");
    sf::Vector2f pos_PlayButton = {
        PlayButton.getPosition().x + PlayButton.getSize().x / 2,
        PlayButton.getPosition().y + PlayButton.getSize().y / 2};
    setTextCenterPosition(Play_, pos_PlayButton);

    screen = 4;
  }
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

  // if multiplayer mode
  if (player.isClient()) {

    next_block = network.listBlocks[player.get_numBlock()];
    player.add_numBlock();

    // if next block is the last of listBlocks, we send a signal to the host
    if (network.listBlocks.find(player.get_numBlock()) ==
        network.listBlocks.end()) {
      network.sendDataToHost(player, "generate new block");
    }
  }
  // if solo mode
  else {
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

  if (player.isHost()) {
    network.sendDataToHost(player, "generate new block");
    network.sendDataToHost(player, "generate new block");
    network.sendDataToHost(player, "generate new block");
    network.sendDataToHost(player, "play");
  }

  if (player.isClient()) {

    TypeDataFromHost = "";
    while (TypeDataFromHost != "play") {
      TypeDataFromHost = network.getDataFromHost(player, other_players);
    }
    current_block = network.listBlocks[0];
    next_block = network.listBlocks[1];

    end_game = false;
  }

  generate_new_next_block();
  current_block = next_block;
  generate_new_next_block();
  current_block->display_block(grid);
  next_block->display_block(little_grid, -3, 0);

  clock.restart();
}

void Game::Initialize_graphics() {

  sf::Color ColorBorder = sf::Color(203, 108, 230);

  /* ---------- INITIALIZATION OF HOMESCREEN---------- */

  soloButton.setSize({WIN_WIDTH / 5.f, WIN_HEIGHT / 10.f});
  multiButton.setSize({WIN_WIDTH / 5.f, WIN_HEIGHT / 10.f});

  soloButton.setPosition(
      {WIN_WIDTH / 3.f - soloButton.getSize().x / 2, WIN_HEIGHT * 4 / 5.f});
  multiButton.setPosition({WIN_WIDTH * 2 / 3.f - multiButton.getSize().x / 2,
                           WIN_HEIGHT * 4 / 5.f});

  soloButton.setOutlineThickness(WIN_WIDTH / 100.f);
  soloButton.setOutlineColor(ColorBorder);
  soloButton.setFillColor(sf::Color::Transparent);

  multiButton.setOutlineThickness(WIN_WIDTH / 100.f);
  multiButton.setOutlineColor(ColorBorder);
  multiButton.setFillColor(sf::Color::Transparent);

  pseudoBox.setSize({WIN_WIDTH * 0.6f, WIN_HEIGHT / 10.f});
  pseudoBox.setPosition(
      {WIN_WIDTH * 0.5f - pseudoBox.getSize().x / 2, WIN_HEIGHT * 6 / 10.f});
  pseudoBox.setOutlineThickness(WIN_WIDTH / 500.f);
  pseudoBox.setOutlineColor(sf::Color::White);
  pseudoBox.setFillColor(sf::Color::Transparent);

  /* ---------- INITIALIZATION OF MULTIPLAYERSCREEN---------- */

  HostButton.setSize({WIN_WIDTH * 0.3f, WIN_HEIGHT * 0.1f});
  ClientButton.setSize({WIN_WIDTH * 0.3f, WIN_HEIGHT * 0.1f});

  HostButton.setPosition(
      {WIN_WIDTH / 3.f - HostButton.getSize().x / 2, WIN_HEIGHT * 0.15f});
  ClientButton.setPosition(
      {WIN_WIDTH * 2 / 3.f - ClientButton.getSize().x / 2, WIN_HEIGHT * 0.15f});

  HostButton.setOutlineThickness(WIN_WIDTH / 500.f);
  HostButton.setOutlineColor(ColorBorder);
  HostButton.setFillColor(ColorBorder);

  ClientButton.setOutlineThickness(WIN_WIDTH / 500.f);
  ClientButton.setOutlineColor(ColorBorder);
  ClientButton.setFillColor(sf::Color::Transparent);

  BackButton.setSize({WIN_WIDTH * 0.15f, WIN_HEIGHT * 0.1f});
  CreateButton.setSize({WIN_WIDTH * 0.15f, WIN_HEIGHT * 0.1f});

  BackButton.setPosition(
      {WIN_WIDTH * 0.4f - BackButton.getSize().x / 2, WIN_HEIGHT * 0.85f});
  CreateButton.setPosition(
      {WIN_WIDTH * 0.6f - CreateButton.getSize().x / 2, WIN_HEIGHT * 0.85f});

  BackButton.setOutlineThickness(WIN_WIDTH / 500.f);
  BackButton.setOutlineColor(sf::Color::White);
  BackButton.setFillColor(sf::Color::Transparent);

  CreateButton.setOutlineThickness(WIN_WIDTH / 500.f);
  CreateButton.setOutlineColor(ColorBorder);
  CreateButton.setFillColor(sf::Color::Transparent);

  ipBox.setSize({WIN_WIDTH * 0.4f, WIN_HEIGHT * 0.1f});
  portBox.setSize({WIN_WIDTH * 0.4f, WIN_HEIGHT * 0.1f});

  ipBox.setPosition(
      {WIN_WIDTH * 0.5f - ipBox.getSize().x / 2, WIN_HEIGHT * 0.4f});
  portBox.setPosition(
      {WIN_WIDTH * 0.5f - portBox.getSize().x / 2, WIN_HEIGHT * 0.6f});

  ipBox.setOutlineThickness(WIN_WIDTH / 1000.f);
  ipBox.setOutlineColor(sf::Color::White);
  ipBox.setFillColor(sf::Color::Transparent);

  portBox.setOutlineThickness(WIN_WIDTH / 1000.f);
  portBox.setOutlineColor(sf::Color::White);
  portBox.setFillColor(sf::Color::Transparent);

  /* ---------- INITIALIZATION OF WAITINGSCREEN---------- */

  PlayButton.setSize({WIN_WIDTH * 0.15f, WIN_HEIGHT * 0.1f});
  PlayButton.setPosition(
      {WIN_WIDTH * 0.5f - PlayButton.getSize().x / 2, WIN_HEIGHT * 0.85f});
  PlayButton.setOutlineThickness(WIN_WIDTH / 500.f);
  PlayButton.setOutlineColor(ColorBorder);
  PlayButton.setFillColor(sf::Color::Transparent);

  /* ---------- INITIALIZATION OF TEXTS ---------- */

  float H_Text_Suivants_Multijoueurs = 1.5 * e;
  sf::Color title_cases_color = sf::Color(255, 222, 89);

  if (!main_font_.loadFromFile(MY_PATH +
                               "/fonts/BigShouldersDisplay.ttf")) {
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

  initialize_text(
      player_score, main_font_, 3,
      {e + L_cases / 2, WIN_HEIGHT - H_Text_Suivants_Multijoueurs - H_22 / 2},
      0.2 * L_cases, std::to_string(player.get_score()), title_cases_color,
      {1, 0.7});

  initialize_text(Title_game, main_font_, 1,
                  {WIN_WIDTH / 2.f, WIN_HEIGHT / 3.f}, 0.2 * WIN_HEIGHT,
                  "TETRIS", title_cases_color, {1, 0.7});

  initialize_text(pickYourName, main_font_, 1,
                  {WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f}, 0.1 * WIN_HEIGHT,
                  "Saisissez votre pseudo", title_cases_color, {1, 0.7});

  initialize_text(playerText, main_font_, 1,
                  {WIN_WIDTH / 2.f, WIN_HEIGHT * 6 / 10.f}, 0.1 * WIN_HEIGHT,
                  playerInput, sf::Color::Cyan, {1, 0.7});

  sf::Vector2f pos_Solo_Button = {
      soloButton.getPosition().x + soloButton.getSize().x / 2,
      soloButton.getPosition().y + soloButton.getSize().y / 2};

  initialize_text(Solo_Button_, main_font_, 1, pos_Solo_Button,
                  0.1 * WIN_HEIGHT, "SOLO", title_cases_color, {1, 0.7});

  sf::Vector2f pos_Multi_Button = {
      multiButton.getPosition().x + multiButton.getSize().x / 2,
      multiButton.getPosition().y + multiButton.getSize().y / 2};

  initialize_text(Multi_Button_, main_font_, 1, pos_Multi_Button,
                  0.1 * WIN_HEIGHT, "MULTI", title_cases_color, {1, 0.7});

  sf::Vector2f pos_HostButton = {
      HostButton.getPosition().x + HostButton.getSize().x / 2,
      HostButton.getPosition().y + HostButton.getSize().y / 2};
  initialize_text(Create_server, main_font_, 1, pos_HostButton,
                  0.05 * WIN_HEIGHT, "Creer un serveur", title_cases_color,
                  {1, 0.7});

  sf::Vector2f pos_ClientButton = {
      ClientButton.getPosition().x + ClientButton.getSize().x / 2,
      ClientButton.getPosition().y + ClientButton.getSize().y / 2};
  initialize_text(Join_server, main_font_, 1, pos_ClientButton,
                  0.05 * WIN_HEIGHT, "Rejoindre un serveur", title_cases_color,
                  {1, 0.7});

  sf::Vector2f pos_BackButton = {
      BackButton.getPosition().x + BackButton.getSize().x / 2,
      BackButton.getPosition().y + BackButton.getSize().y / 2};
  initialize_text(GoBack_, main_font_, 1, pos_BackButton, 0.05 * WIN_HEIGHT,
                  "Annuler", sf::Color::White, {1, 0.7});

  sf::Vector2f pos_CreateButton = {
      CreateButton.getPosition().x + CreateButton.getSize().x / 2,
      CreateButton.getPosition().y + CreateButton.getSize().y / 2};
  initialize_text(Create_, main_font_, 1, pos_CreateButton, 0.05 * WIN_HEIGHT,
                  "Creer", title_cases_color, {1, 0.7});

  initialize_text(ip_, main_font_, 6,
                  {ipBox.getPosition().x - 0.02f * WIN_HEIGHT,
                   ipBox.getPosition().y + ipBox.getSize().y / 2},
                  0.05 * WIN_HEIGHT, "ip serveur : ", sf::Color::White,
                  {1, 0.7});

  initialize_text(port_, main_font_, 6,
                  {portBox.getPosition().x - 0.02f * WIN_HEIGHT,
                   portBox.getPosition().y + portBox.getSize().y / 2},
                  0.05 * WIN_HEIGHT, "Mot de passe : ", sf::Color::White,
                  {1, 0.7});

  ipString = network.get_ip().toString();
  initialize_text(ipInput, main_font_, 5,
                  {ipBox.getPosition().x + 0.05f * WIN_WIDTH,
                   ipBox.getPosition().y + ipBox.getSize().y * 0.5f},
                  0.05 * WIN_HEIGHT, ipString, sf::Color::White, {1, 0.7});

  portString = std::to_string(network.get_port());
  initialize_text(portInput, main_font_, 5,
                  {portBox.getPosition().x + 0.05f * WIN_WIDTH,
                   portBox.getPosition().y + portBox.getSize().y * 0.5f},
                  0.05 * WIN_HEIGHT, portString, sf::Color::White, {1, 0.7});

  initialize_text(Title_waiting, main_font_, 1,
                  {WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.2f}, 0.08 * WIN_WIDTH,
                  "En attente des autres joueurs", title_cases_color, {1, 0.7});

  sf::Vector2f pos_PlayButton = {
      PlayButton.getPosition().x + PlayButton.getSize().x / 2,
      PlayButton.getPosition().y + PlayButton.getSize().y / 2};
  initialize_text(Play_, main_font_, 1, pos_PlayButton, 0.05 * WIN_HEIGHT,
                  "Creer", title_cases_color, {1, 0.7});

  initialize_text(Quitting_, main_font_, 1,
                  {WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f}, 0.05 * WIN_WIDTH,
                  "Serveur coupe", title_cases_color, {1, 0.7});

  /* ---------- INITIALIZATION OF BACKGROUNDS ---------- */

  float blurGrid_Opacity = 180;

  if (!bgTexture.loadFromFile(MY_PATH + "/images/background.png")) {
    // error...
  }
  bgSprite.setTexture(bgTexture);
  scaleToMinSize(bgSprite, WIN_HEIGHT, WIN_WIDTH);

  blurGrid_.setPosition({2 * e + L_cases, e});
  blurGrid_.setSize({WIN_WIDTH - 4 * e - 2 * L_cases, WIN_HEIGHT - 2 * e});
  blurGrid_.setFillColor(sf::Color(0, 0, 0, blurGrid_Opacity));

  /* ---------- INITIALIZATION OF LINES ---------- */

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

    if (event.key.code == sf::Keyboard::Q) {
      if (player.isHost()) {
        network.sendDataToHost(player, "server down");
        // if success :
        screen = 1;
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