#include "Card.h"
#include "Game.h"
#include <SDL2/SDL_image.h>

Card::Card() {}
Card::~Card() {
  if (m_texture) SDL_DestroyTexture(m_texture);
}

bool Card::load(const std::string& file, int x, int y, int w, int h) {
  SDL_Surface* tmp = IMG_Load(file.c_str());
  if (!tmp) return false;
  m_texture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), tmp);
  SDL_FreeSurface(tmp);
  
  m_rect = {x, y, w, h};
  return m_texture != nullptr;
}

void Card::render(SDL_Renderer* renderer) {
  if (m_texture) {
    // source rect = nullptr for using the whole texture
    SDL_RenderCopy(renderer, m_texture, nullptr, &m_rect);
  }
}