#pragma once 
#include <string>
#include <vector>
#include "Layer.h"
#include "ObjectLayer.h"

class TileLayer;

struct Tileset {
  int firstGridID;
  int tileWidth;
  int tileHeight;
  int spacing;
  int margin;
  int width; // of whole Tileset .png [pixels] 
  int height; // of whole Tileset .png [pixels]
  int numColumns;
  std::string name; // Tileset name
};

class Level {
public:
  ~Level();

  void update();
  void render();

  std::vector<Tileset>* getTilesets() { return &m_tilesets; }
  std::vector<Layer*>* getLayers() { return &m_layers; }
  std::vector<TileLayer*>* getCollisionLayers() { return &m_collisionLayers; }
  ObjectLayer* getObjectLayer();

private:
  friend class LevelParser;
  Level() {} // put constructor in private, to create Level only with LevelParser
  std::vector<Layer*> m_layers;
  std::vector<Tileset> m_tilesets; // will be push_back() in LevelParser (parseTilesets() function)
  std::vector<TileLayer*> m_collisionLayers;
};