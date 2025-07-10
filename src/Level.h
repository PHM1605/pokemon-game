#pragma once 
#include "Layer.h"

class TileLayer;

struct Tileset {
  int firstGridID;
  int tileWidth;
  int tileHeight;
  int spacing;
  int margin;
  int width; // of whole Tileset .png 
  int height; // of whole Tileset .png
  int numColumns;
  std::string name; // Tileset name
};

class Level {
public:
  ~Level();

private:
  friend class LevelParser;
  Level() {} // put constructor in private, to create Level only with LevelParser
};