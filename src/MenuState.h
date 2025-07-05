#pragma once 
#include "GameState.h"

class MenuState: public GameState {
public:
  void update() override;
  void render(SDL_Renderer* renderer) override;
};