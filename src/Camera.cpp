#include "Camera.h"
#include "Game.h"

Camera* Camera::s_pCamera = nullptr;

Camera::Camera():
  m_pTarget(nullptr), m_position(0,0)
{}

// Camera top-left is adjusted so that Player is at screen center
const Vector2D Camera::getPosition() const {
  if (m_pTarget != 0) {
    Vector2D pos (
      m_pTarget->getX() - Game::Instance()->getGameWidth()/2, 
      m_pTarget->getY() - Game::Instance()->getGameHeight()/2);
    if (pos.getX() < 0)
      pos.setX(0);
    if (pos.getY() < 0) 
      pos.setY(0);
    return pos;
  }
  return m_position;
}

void Camera::update(Vector2D velocity) {
  m_position += velocity;
  if (m_position.getX() < 0) {
    m_position.setX(0);
  }
  if (m_position.getY() < 0) {
    m_position.setY(0);
  }
}