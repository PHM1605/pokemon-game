#include "Game.h"
#include "Player.h"
#include "TextureManager.h"
#include <SDL2/SDL_image.h>

Player::Player():
  GameObject()
{}

void Player::load(std::unique_ptr<LoaderParams> const &pParams) {
  GameObject::load(std::move(pParams));
}

void Player::handleInput(const Uint8* keystate) {
  if (keystate[SDL_SCANCODE_UP]) m_rect.y -= m_speed;
  if (keystate[SDL_SCANCODE_DOWN]) m_rect.y += m_speed;
  if (keystate[SDL_SCANCODE_LEFT]) m_rect.x -= m_speed;
  if (keystate[SDL_SCANCODE_RIGHT]) m_rect.x += m_speed;
}

void Player::update() {

}

void Player::render() {
  if (m_bFlipped) {
    TextureManager::Instance()->drawFrame(
      m_textureID, 
      (Uint32)m_position.getX(), (Uint32)m_position.getY(),
      m_width, m_height, m_currentRow, m_currentFrame,
      Game::Instance()->getRenderer(),
      m_angle, m_alpha, SDL_FLIP_HORIZONTAL);
  } else {
    TextureManager::Instance()->drawFrame(
      m_textureID,
      (Uint32)m_position.getX(), (Uint32)m_position.getY(),
      m_width, m_height, m_currentRow, m_currentFrame,
      Game::Instance()->getRenderer(),
      m_angle, m_alpha);
  }
}

SDL_Rect Player::getRect() const {
  return m_rect;
}