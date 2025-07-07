#pragma once 
#include "GameState.h"

class MenuState: public GameState {
public:
  void update(const SDL_Event& e) override;
  void render(SDL_Renderer* renderer) override;
};