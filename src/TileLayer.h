#pragma once 
#include <vector>
#include "Layer.h"
#include "Level.h"

class TileLayer: public Layer {
public:
  TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset>& tilesets);
  virtual ~TileLayer() {}

  virtual void update() {}
  virtual void render();

  void setTileIDs(const std::vector<std::vector<int>>& data) { m_tileIDs = data; }
  const std::vector<std::vector<int>>& getTileIDs() { return m_tileIDs; }

  int getTileSize() { return m_tileSize; }
  void setTileSize(int tileSize) { m_tileSize = tileSize; }

  int getMapWidth() { return m_numColumns; }
  void setMapWidth(int mapWidth) { m_numColumns = mapWidth; }

  int getMapHeight() { return m_numRows; }
  void setMapHeight(int mapHeight) { m_numRows = mapHeight; }

  // that small Tile belongs to which Tileset image?
  Tileset getTilesetByID(int tileID); 

private:
  // m_numColumns: whole TileLayer width [cell]
  // m_numRows: whole TileLayer height [cell]
  int m_numColumns;
  int m_numRows;
  int m_tileSize;
  bool m_bCollision;   // TileLayer is collision layer or not

  const std::vector<Tileset>& m_tilesets;
  std::vector<std::vector<int>> m_tileIDs; // our main data
};