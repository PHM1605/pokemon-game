#include <iostream>
#include <src/Game.h>
#include "SDL2/SDL.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS; // time between 2 frames (in ms)

int main(int argc, char** argv) {
  Uint32 frameStart, frameTime;
  if (Game::Instance()->init("Yu-Gi-Oh! SDL2", 1280, 720, false)) {
    std::cout << "game init success!\n";
    while (Game::Instance()->running()) {
      frameStart = SDL_GetTicks();
      Game::Instance()->handleEvents();
      Game::Instance()->update();
      Game::Instance()->render();

      frameTime  = SDL_GetTicks() - frameStart;
      if (frameTime < DELAY_TIME) {
        SDL_Delay((int)(DELAY_TIME - frameTime));
      }
    }
  } else {
    std::cout << "game init failure - " << SDL_GetError() << "\n";
    return -1;
  }
  
  std::cout << "game closing...\n";
  Game::Instance()->clean();

  return 0;
}