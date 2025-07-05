#pragma once
#include <SDL2/SDL.h>
#include <string>

class Card {
public:
  Card();
  ~Card();

  bool load(const std::string& file, int x, int y, int w, int h);
  void render(SDL_Renderer* renderer);

private:
  SDL_Texture* m_texture = nullptr;
  SDL_Rect m_rect; // destination rectangular
};