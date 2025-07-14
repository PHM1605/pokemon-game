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
  // m_rect = {static_cast<int>(m_position.getX()), static_cast<int>(m_position.getY()), m_width, m_height};
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
  handleMovement(m_velocity);
}

void Player::handleInput() {
  // assuming we have only 1 collision layer
  TileLayer* collisionLayer = (*m_pLevel->getCollisionLayers())[0];
  int tileSize = collisionLayer->getTileSize();
  if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) && m_position.getX() < tileSize*collisionLayer->getMapWidth()-m_width) {
    m_bMoveRight = true;
    m_bMoveLeft = false;
    m_bMoveUp = false;
    m_bMoveDown = false;
  } 
  else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && m_position.getX()>0) {
    m_bMoveLeft = true;
    m_bMoveRight = false;
    m_bMoveUp = false;
    m_bMoveDown = false;
  } 
  else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) && m_position.getY() > 0) {
    m_bMoveLeft = false;
    m_bMoveRight = false;
    m_bMoveUp = true;
    m_bMoveDown = false;
  } 
  else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) && m_position.getY() < tileSize*collisionLayer->getMapHeight()-m_height) {
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

void Player::handleMovement(Vector2D velocity) {
  Vector2D newPos = m_position;
  newPos.setX(newPos.getX() + velocity.getX());
  if (!checkCollideTile(newPos)) {
    m_position.setX(newPos.getX());
  } else {
    m_velocity.setX(0);
  }

  newPos = m_position;
  newPos.setY(newPos.getY() + velocity.getY());
  if (!checkCollideTile(newPos)) {
    m_position.setY(newPos.getY());
  } else {
    m_velocity.setY(0);
  }
}

bool Player::checkCollideTile(Vector2D newPos) {
  // we have only 1 collision layer
  TileLayer* pCollisionLayer = (*m_pLevel->getCollisionLayers())[0];
  std::vector<std::vector<int>> tiles = pCollisionLayer->getTileIDs();
  int tileSize = pCollisionLayer->getTileSize();

  // startPos is a bit inside Object top-left
  // endPos is a bit inside Object bottom-right
  Vector2D startPos(newPos.getX()+1, newPos.getY()+1);
  Vector2D endPos(newPos.getX()+m_width-1, newPos.getY()+m_height-1);
  // whether any point inside Object belongs to a Collidable cell (Tile with id != 0)
  int tileColumn,tileRow, tileID;
  for (int i=startPos.getX(); i<endPos.getX(); i++) {
    for (int j=startPos.getY(); j<endPos.getY(); j++) {
      tileColumn = i / tileSize;
      tileRow = j / tileSize;
      tileID = tiles[tileRow][tileColumn];
      if (tileID != 0)
        return true;
    }
  }
  return false;
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
