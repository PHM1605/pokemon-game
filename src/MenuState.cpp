#include "DuelState.h"
#include "Game.h"
#include "MenuState.h"
#include "StoryState.h"

void MenuState::update() {
  SDL_Event e;
  while(SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      SDL_Quit();
      exit(0);
    }
    // pressing enter to move to the next state
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
      Game::Instance()->changeState(std::make_shared<StoryState>());
    }
  }
}

void MenuState::render(SDL_Renderer* renderer) {
  
}