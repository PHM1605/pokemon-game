#include <iostream>
#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"
#include "TileLayer.h"

TileLayer::TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset>& tilesets):
  m_tileSize(tileSize), m_tilesets(tilesets) 
{
  m_numColumns = mapWidth; // cell 
  m_numRows = mapHeight; // cell 
}

void TileLayer::render() {
  // draw only the Tiles which are 1/ value != 0 and 2/ within Camera range
  for (int i=0; i<m_numRows; i++) {
    for (int j=0; j<m_numColumns; j++) {
      int id = m_tileIDs[i][j];
      // if Tile value == 0 -> not draw
      if (id == 0) continue;
      // if column < Camera or > Camera width then not draw
      Vector2D camPos = Camera::Instance()->getPosition();
      int offsetX = j*m_tileSize - camPos.getX();
      if (offsetX < -m_tileSize || offsetX > Game::Instance()->getGameWidth())
        continue;
      // if row < Camera or > Camera height then not draw
      int offsetY = i*m_tileSize - camPos.getY();
      if (offsetY < -m_tileSize || offsetY > Game::Instance()->getGameHeight())
        continue;
      // draw within-range tiles
      Tileset tileset = getTilesetByID(id);
      id--; // as meaningful TilemapID starts from 1
      TextureManager::Instance()->drawTile(
        tileset.name,
        tileset.margin, tileset.spacing,
        j*m_tileSize-camPos.getX(), i*m_tileSize-camPos.getY(), // destination to draw on screen
        m_tileSize, m_tileSize,
        (id-(tileset.firstGridID-1)) / tileset.numColumns, (id-(tileset.firstGridID-1)) % tileset.numColumns,
        Game::Instance()->getRenderer()
      );
    }
  }
}

// tileID = 15 belongs to which Tileset => return Tileset data
// 1 Tileset only => return directly
// 2 Tilesets or more => check if tileID within range
Tileset TileLayer::getTilesetByID(int tileID) {
  for (int i=0; i<m_tilesets.size(); i++) {
    if (i < m_tilesets.size()-1) {
      if (tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i+1].firstGridID)
        return m_tilesets[i];
      else 
        return m_tilesets[i];
    }
  }
  std::cout << "did not find Tileset, returning empty tileset\n";
  Tileset t;
  return t;
}