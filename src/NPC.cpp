#include "NPC.h"
#include <SDL2/SDL_image.h>

bool NPC::load(SDL_Renderer* renderer, const std::string& file, int x, int y) {
  SDL_Surface* surf = IMG_Load(file.c_str());
  if (!surf) return false;
  m_texture = SDL_CreateTextureFromSurface(renderer, surf);
  SDL_FreeSurface(surf);
  m_rect = {x, y, 48, 48};
  return true;
}

void NPC::render(SDL_Renderer* renderer) {
  SDL_RenderCopy(renderer, m_texture, nullptr, &m_rect);
}

SDL_Rect NPC::getRect() const {
  return m_rect;
}