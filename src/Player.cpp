#include "Camera.h"
#include "Game.h"
#include "InputHandler.h"
#include "Player.h"
#include "TextureManager.h"
#include <SDL2/SDL_image.h>

Player::Player():
  GameObject()
{
  m_bMoveRight = false;
  m_bMoveLeft = false;
  m_bMoveUp = false;
  m_bMoveDown = false;
}

void Player::load(std::unique_ptr<LoaderParams> pParams) {
  m_pParams = std::move(pParams);

  m_position.setX(m_pParams->getX());
  m_position.setY(m_pParams->getY());
  m_width = m_pParams->getWidth();
  m_height = m_pParams->getHeight();
  m_textureID = m_pParams->getTextureID();
  m_numFrames = m_pParams->getNumFrames();
  m_rect = {static_cast<int>(m_position.getX()), static_cast<int>(m_position.getY()), m_width, m_height};
  Camera::Instance()->setTarget(&m_position);
}

void Player::update() {
  // updating Bool status flags
  handleInput();
  // change speed accordingly
  if (m_bMoveLeft) {
    m_velocity.setX(-m_speed);
    m_velocity.setY(0);
  } else if (m_bMoveRight) {
    m_velocity.setX(m_speed);
    m_velocity.setY(0);
  } else if (m_bMoveUp) {
    m_velocity.setX(0);
    m_velocity.setY(-m_speed);
  } else if (m_bMoveDown) {
    m_velocity.setX(0);
    m_velocity.setY(m_speed);
  } else {
    m_velocity.setX(0);
    m_velocity.setY(0);
  }
  // update position accordingly (to be rendered later)
  m_position.setX(m_position.getX() + m_velocity.getX());
  m_position.setY(m_position.getY() + m_velocity.getY());
}

// void Player::handleInput(const Uint8* keystate) {
//   if (keystate[SDL_SCANCODE_UP]) m_rect.y -= m_speed;
//   if (keystate[SDL_SCANCODE_DOWN]) m_rect.y += m_speed;
//   if (keystate[SDL_SCANCODE_LEFT]) m_rect.x -= m_speed;
//   if (keystate[SDL_SCANCODE_RIGHT]) m_rect.x += m_speed;
// }
#include <iostream>
void Player::handleInput() {
  // assuming we have only 1 collision layer
  std::cout <<"DEBUGG: " << (*m_pCollisionLayers).size();
  TileLayer* collisionLayer = (*m_pCollisionLayers->begin());
  // if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) && m_position.getX() < collisionLayer->getMapWidth()*(collisionLayer->getTileSize()-1)) {
  if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {  
    m_bMoveRight = true;
    m_bMoveLeft = false;
    m_bMoveUp = false;
    m_bMoveDown = false;
  } 
  else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
  // else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && m_position.getX()>0) {
    m_bMoveLeft = true;
    m_bMoveRight = false;
    m_bMoveUp = false;
    m_bMoveDown = false;
  } 
  else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
  // else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) && m_position.getY() > 0) {
    m_bMoveLeft = false;
    m_bMoveRight = false;
    m_bMoveUp = true;
    m_bMoveDown = false;
  } 
  else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) ) {
  // else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) && m_position.getY() < (collisionLayer->getMapHeight()-collisionLayer->getTileSize())) {
    m_bMoveLeft = false;
    m_bMoveRight = false;
    m_bMoveUp = false;
    m_bMoveDown = true;
  } else {
    m_bMoveLeft = false;
    m_bMoveRight = false;
    m_bMoveUp = false;
    m_bMoveDown = false;
  }
}

void Player::render() {
  Vector2D camPos = Camera::Instance()->getPosition();
  if (m_bFlipped) {    
    TextureManager::Instance()->drawFrame(
      m_textureID, 
      (Uint32)m_position.getX()-camPos.getX(), (Uint32)m_position.getY()-camPos.getY(),
      m_width, m_height, m_currentRow, m_currentFrame,
      Game::Instance()->getRenderer(),
      m_angle, m_alpha, SDL_FLIP_HORIZONTAL);
  } else {
    TextureManager::Instance()->drawFrame(
      m_textureID,
      (Uint32)m_position.getX()-camPos.getX(), (Uint32)m_position.getY()-camPos.getY(),
      m_width, m_height, m_currentRow, m_currentFrame,
      Game::Instance()->getRenderer(),
      m_angle, m_alpha);
  }
}

SDL_Rect Player::getRect() const {
  return m_rect;
}