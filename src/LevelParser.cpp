#include "Game.h"
#include "LevelParser.h"
#include "TextureManager.h"
#include "tinyxml.h"
#include "zlib.h"

Level* LevelParser::parseLevel(const char* levelFile) {
  TiXmlDocument levelDocument;
  levelDocument.LoadFile(levelFile);
  Level* pLevel = new Level();
  // pRoot: <map version="1.0" orientation="orthogonal" width="200" height="15" tilewidth="32" tileheight="32">
  // width, height: in [tile]
  TiXmlElement* pRoot = levelDocument.RootElement();
  std::cout << "Loading level:\n" << "Width: " << pRoot->Attribute("width") << " - Height: " << pRoot->Attribute("height") << "\n";
  pRoot->Attribute("tilewidth", &m_tileSize);
  pRoot->Attribute("width", &m_width);
  pRoot->Attribute("height", &m_height);
  
  // <properties>
  //   <property name="npc" value="assets/npc.png"/>
  //   <property name="opponent" value="assets/opponent.png"/>
  // </properties>
  TiXmlElement* pProperties = pRoot->FirstChildElement();
  for (TiXmlElement* e = pProperties->FirstChildElement(); e!=NULL; e=e->NextSiblingElement()) {
    if (e->Value() == std::string("property"))
      parseTextures(e);
  }

  // <tileset firstgid="1" name="blocks1" tilewidth="32" tileheight="32" spacing="2" margin="2">
  //   <image source="blocks1.png" width="614" height="376"/>
  // </tileset>
  for (TiXmlElement* e = pRoot->FirstChildElement(); e != nullptr; e=e->NextSiblingElement()) {
    if (e->Value() == std::string("tileset"))
      parseTilesets(e, pLevel->getTilesets());
  }
}

// pTextureRoot: <property name="npc1" value="assets/npc.png"/>
// name: ID of that Texture
// value: path of .png
void LevelParser::parseTextures(TiXmlElement* pTextureRoot) {
  std::cout << "adding texture " << pTextureRoot->Attribute("value") << " with ID " << pTextureRoot->Attribute("name") << std::endl;
  TextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"), Game::Instance()->getRenderer());
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets) {

}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers, Level* pLevel) {

}

void LevelParser::parseTileLayer(
  TiXmlElement* pTileElement, 
  std::vector<Layer*>* pLayers, 
  const std::vector<Tileset>* pTilesets, 
  std::vector<TileLayer*>* pCollisionLayers) {

}