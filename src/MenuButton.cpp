#include "Game.h"
#include "MenuButton.h"
#include "TextureManager.h"

MenuButton::MenuButton():
  GameObject() 
{}

void MenuButton::load(std::unique_ptr<LoaderParams>const pParams) {
  m_position = Vector2D(pParams->getX(), pParams->getY());
  m_width = pParams->getWidth();
  m_height = pParams->getHeight();
  m_textureID = pParams->getTextureID();
  m_numFrames = pParams->getNumFrames();
  m_currentFrame = NOT_CHOSEN;
}
void MenuButton::render() {
  TextureManager::Instance()->drawFrame(
    m_textureID,
    (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height,
    m_currentRow, m_currentFrame,
    Game::Instance()->getRenderer(),
    m_angle, m_alpha
  );
}

void MenuButton::update() {

}