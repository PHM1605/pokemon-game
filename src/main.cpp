#include <iostream>
#include <src/Game.h>
#include "SDL2/SDL.h"

int main(int argc, char** argv) {
  Uint32 frameStart, frameTime;
  if (Game::Instance()->init("Yu-Gi-Oh! SDL2", 1280, 720);
  Game::Instance()->run();
  Game::Instance()->clean();

  return 0;
}