#include <SDL2/SDL_image.h>
#include "Game.h"
#include "NPC.h"
#include "TextureManager.h"

void NPC::load(std::unique_ptr<LoaderParams> const &pParams) {
  m_position = Vector2D(pParams->getX(), pParams->getY());
  m_width = pParams->getWidth();
  m_height = pParams->getHeight();
  m_textureID = pParams->getTextureID();
  m_numFrames = pParams->getNumFrames();
}

void NPC::render() {
  TextureManager::Instance()->drawFrame(
    m_textureID,
    (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height,
    m_currentRow, m_currentFrame,
    Game::Instance()->getRenderer(),
    m_angle, m_alpha
  );
}

// SDL_Rect NPC::getRect() const {
//   return m_rect;
// }