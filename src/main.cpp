#include <cstdio>

#include "../inc/game.hpp"

using namespace TETRIS;

int main (){
    TETRIS::Game* game = new TETRIS::Game();
    game->Run();
    delete game;
    return 0;
}