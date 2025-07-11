#include "Background.h"
#include "Game.h"
#include "TextureManager.h"

Background::Background():
  GameObject()
{}

void Background::load(std::unique_ptr<LoaderParams> pParams) {
  m_pParams = std::move(pParams);

  m_position.setX(m_pParams->getX());
  m_position.setY(m_pParams->getY());
  m_width = m_pParams->getWidth();
  m_height = m_pParams->getHeight();
  m_textureID = m_pParams->getTextureID();
  m_numFrames = m_pParams->getNumFrames();
}

void Background::render() {
  TextureManager::Instance()->drawFrame(
    m_textureID,
    static_cast<int>(m_position.getX()),
    static_cast<int>(m_position.getY()),
    m_width, m_height,
    0, 0,
    Game::Instance()->getRenderer(),
    m_angle, m_alpha
  );
}

void Background::update() {

}

void Background::clean() {

}