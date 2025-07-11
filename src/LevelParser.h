#pragma once 
#include <vector>
#include "Level.h"
#include "tinyxml.h"

class LevelParser {
public:
  Level* parseLevel(const char* mapFile);

private:
  void parseTextures(TiXmlElement* pTextureRoot);
  void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
  // pLayers: contains BOTH ObjectLayer + TileLayer (TileLayer includes Overlay and Collision)
  void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers,const std::vector<Tileset> *pTilesets, std::vector<TileLayer*> *pCollisionLayers);
  void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers, Level* pLevel);
  
  int m_tileSize; // 32 pixels
  int m_width; // [cell]
  int m_height; // [cell]
};