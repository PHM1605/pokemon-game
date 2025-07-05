#pragma once 
#include <SDL2/SDL.h>

class GameState {
public:
  virtual void update() = 0;
  virtual void render(SDL_Renderer* renderer) = 0;
  virtual ~GameState() = default;
};