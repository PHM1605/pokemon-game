#include "Game.h"
#include "LevelParser.h"
#include "TextureManager.h"
#include "TileLayer.h"
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

  // <layer name="Overlay" width="200" height="15">
  //   <data encoding="base64" compression="zlib">
  //     eJztzrsNgDAUA8BEQozA/psBIwQWIJT8miAonu4kN3bjlAAAAAAAAAD+M9ZMNXPjHuUD3Ck1S83auH/1ofz8AZ50+d0e5QPs+nzMkK/deY/4AQCIZwOTaBfU
  //   </data>
  // </layer>

  // <layer name="Collision" width="200" height="15">
  //   <properties>
  //     <property name="collidable" value="true"/>
  //   </properties>
  //   <data encoding="base64" compression="zlib">
  //     eJztlg0KgzAMRtNr7G7bNTc28B47g/MOQ6QgXZKirfPvPfgYqJOY+lJbEWmdABwB7x0vCcARwA8AG/wAsMEPABv8ALDBDwAb/ACwwQ8AG/wYuCcB6DmzH2MfnklAJ50f6Vw52ow5mx+eE306wQ+NtGcRrYcx415fg8gt2L9b9epsfnjruef9w5rrte5r9adWPzWvtsBSfnj77j/yMI7HNfjI7xo2oq/nUrV43yRTvmO0uR6fr7T23N4wPnYJQ0r90PaftTL3/fdmxcvJO3N+apqC/2p1a+upXTs3XeZ8pHRO16q3VqI7Vtaur3a+mGxSJw==
  //   </data>
  // </layer>
  
  // <objectgroup name="Object Layer 1" width="200" height="15">
  //   <object name="npc1" type="NPC" x="718" y="335" width="32" height="32">
  //     <properties>
  //       <property name="numFrames" value="4"/>
  //       <property name="textureHeight" value="34"/>
  //       <property name="textureID" value="snail"/>
  //       <property name="textureWidth" value="34"/>
  //     </properties>
  //   </object>
  // </objectgroup>
  for (TiXmlElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
    if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer")) {
      if (e->FirstChildElement()->Value() == std::string("object")) {
        parseObjectLayer(e, pLevel->getLayers(), pLevel);
      } 
      else if (
        e->FirstChildElement()->Value() == std::string("data")
        || (e->FirstChildElement()->NextSiblingElement() != 0 && e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data"))) {
          parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets(), pLevel->getCollisionLayers());
        }
    }
  }
}

// pTextureRoot: <property name="npc1" value="assets/npc.png"/>
// name: ID of that Texture
// value: path of .png
void LevelParser::parseTextures(TiXmlElement* pTextureRoot) {
  std::cout << "adding texture " << pTextureRoot->Attribute("value") << " with ID " << pTextureRoot->Attribute("name") << std::endl;
  TextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"), Game::Instance()->getRenderer());
}

// pTilesetRoot: 
// <tileset firstgid="1" name="blocks1" tilewidth="32" tileheight="32" spacing="2" margin="2">
//   <image source="blocks1.png" width="614" height="376"/>
// </tileset>
void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets) {
  std::string assetsTag = "assets/"; 
  std::cout << "adding texture " << pTilesetRoot->FirstChildElement()->Attribute("source") << " with ID" << pTilesetRoot->Attribute("name") << "\n";
  TextureManager::Instance()->load(
    assetsTag.append(pTilesetRoot->FirstChildElement()->Attribute("source")), // "assets/blocks1.png"
    pTilesetRoot->Attribute("name"), // ID file that Texture: "blocks1"
    Game::Instance()->getRenderer()
  );

  Tileset tileset;
  pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width); // [pixels]
  pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height); // [pixels]
  pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
  pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth); // 32 pixels
  pTilesetRoot->Attribute("tileheight", &tileset.tileHeight); // 32 pixels
  pTilesetRoot->Attribute("spacing", &tileset.spacing);
  pTilesetRoot->Attribute("margin", &tileset.margin);
  tileset.name = pTilesetRoot->Attribute("name");
  tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing); // [cell]

  pTilesets->push_back(tileset);
}

// <objectgroup name="Object Layer 1" width="200" height="15">
//   <object name="npc1" type="NPC" x="718" y="335" width="32" height="32">
//     <properties>
//       <property name="numFrames" value="4"/>
//       <property name="textureHeight" value="34"/>
//       <property name="textureID" value="snail"/>
//       <property name="textureWidth" value="34"/>
//     </properties>
//   </object>
// </objectgroup>
void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers, Level* pLevel) {
  
}

void LevelParser::parseTileLayer(
  TiXmlElement* pTileElement, 
  std::vector<Layer*>* pLayers, 
  const std::vector<Tileset>* pTilesets, 
  std::vector<TileLayer*>* pCollisionLayers) 
{
  // m_width, m_height: [cell]
  TileLayer* pTileLayer = new TileLayer(m_tileSize, m_width, m_height, *pTilesets);
  pLayers->push_back(pTileLayer);
}