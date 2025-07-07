#include <iostream>
#include "DuelState.h"
#include "Game.h"
#include "MenuState.h"
#include "StoryState.h"

void MenuState::update(const SDL_Event& e) {
  std::cout << "TYPE INNER: " << e.type << std::endl;
  if (e.type == SDL_QUIT) {
    std::cout << "QUITTING\n";
    SDL_Quit();
    exit(0);
  }
  // pressing enter to move to the next state
  if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
    std::cout << "PRESSING ENTER\n";
    Game::Instance()->changeState(std::make_shared<StoryState>());
  }
}

void MenuState::render(SDL_Renderer* renderer) {
}