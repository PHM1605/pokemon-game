#include <SDL2/SDL_image.h>
#include "Camera.h"
#include "Game.h"
#include "NPC.h"
#include "TextureManager.h"

void NPC::load(std::unique_ptr<LoaderParams> const pParams) {
  m_position = Vector2D(pParams->getX(), pParams->getY());
  m_width = pParams->getWidth();
  m_height = pParams->getHeight();
  m_textureID = pParams->getTextureID();
  m_numFrames = pParams->getNumFrames();
}
#include <iostream>
void NPC::render() {
  Vector2D camPos = Camera::Instance()->getPosition();
  TextureManager::Instance()->drawFrame(
    m_textureID,
    (Uint32)m_position.getX()-camPos.getX(), (Uint32)m_position.getY()-camPos.getY(), m_width, m_height,
    m_currentRow, m_currentFrame,
    Game::Instance()->getRenderer(),
    m_angle, m_alpha
  );
}

void NPC::update() {
  
}

// SDL_Rect NPC::getRect() const {
//   return m_rect;
// }