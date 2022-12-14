#include <cstdio>

#include "../inc/game.hpp"

using namespace tetris;

int main() {
  tetris::Game *game = new tetris::Game();

  game->Run();
  delete game;
  return 0;
}