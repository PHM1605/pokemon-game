#include "Player.h"
#include <SDL2/SDL_image.h>

Player::Player():
  GameObject()
{}

bool Player::load(SDL_Renderer* renderer, const std::string& file, int x, int y) {
  SDL_Surface* surf = IMG_Load(file.c_str()); 
  if (!surf) return false;
  m_texture = SDL_CreateTextureFromSurface(renderer, surf);
  SDL_FreeSurface(surf);
  m_rect = {x, y, 48, 48};
  return true;
}

void Player::handleInput(const Uint8* keystate) {
  if (keystate[SDL_SCANCODE_UP]) m_rect.y -= m_speed;
  if (keystate[SDL_SCANCODE_DOWN]) m_rect.y += m_speed;
  if (keystate[SDL_SCANCODE_LEFT]) m_rect.x -= m_speed;
  if (keystate[SDL_SCANCODE_RIGHT]) m_rect.x += m_speed;
}

void Player::update() {

}

void Player::render(SDL_Renderer* renderer) {
  SDL_RenderCopy(renderer, m_texture, nullptr, &m_rect);

}

SDL_Rect Player::getRect() const {
  return m_rect;
}