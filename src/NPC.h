#pragma once 
#include <SDL2/SDL.h>
#include<string>

class NPC {
public:
  bool load(SDL_Renderer* renderer, const std::string& file, int x, int y);
  void render(SDL_Renderer* renderer);
  SDL_Rect getRect() const;

private:
  SDL_Texture* m_texture = nullptr;
  SDL_Rect m_rect;
};
