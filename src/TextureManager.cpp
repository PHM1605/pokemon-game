#include <iostream>
#include <SDL2/SDL_image.h>
#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = nullptr;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer) {
  SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
  if (pTempSurface == 0) {
    std::cout << IMG_GetError();
    return false;
  }
  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
  SDL_FreeSurface(pTempSurface);
  if(pTexture != 0) {
    m_textureMap[id] = pTexture;
    return true;
  }
  return false;
}

// draw the whole image 
// x, y: destination to (on Game screen, in pixels)
// width, height: in pixels
void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
  SDL_Rect srcRect;
  SDL_Rect destRect; 
  
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;
  // 0, 0 means 'no rotation origin, no rotation angle'
  SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

// draw animation
void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip) {

}

// draw a small part [width,height] of the source image
// x, y: destination to draw to (on Game screen, in pixels)
// width, height: e.g. [32,32] if Tile case
void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer) {

}

void TextureManager::clean() {
  for (auto& pair: m_textureMap) {
    SDL_DestroyTexture(pair.second);
  }
  m_textureMap.clear();
}

void TextureManager::clearFromTextureMap(std::string id) {
  auto it = m_textureMap.find(id);
  if (it != m_textureMap.end()) {
    SDL_DestroyTexture(it->second);
    m_textureMap.erase(id);
  }
}
