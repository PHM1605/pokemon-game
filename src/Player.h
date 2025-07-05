#pragma once
#include <SDL2/SDL.h>
#include <string>

class Player {
public:
  bool load(SDL_Renderer* renderer, const std::string& file, int x, int y);
  void handleInput(const Uint8* keyState);
  void update();
  void render(SDL_Renderer* renderer);
  SDL_Rect getRect() const;

private:
  SDL_Texture* m_texture = nullptr;
  SDL_Rect m_rect;
  int m_speed = 4;
};