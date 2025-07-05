#pragma once 
#include "GameState.h"

class StoryState: public GameState {
public:
  StoryState();
  void update() override;
  void render(SDL_Renderer* renderer) override;

private:
  int m_timer = 0;
};