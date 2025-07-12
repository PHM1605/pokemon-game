#include "base64.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "LevelParser.h"
#include "ObjectLayer.h"
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
  // 2 TileLayers: "Overlay", "Collision"; 1 Object Layers: "Object Layer 1"
  std::cout << "#tile layers: " << pLevel->getLayers()->size() << std::endl;
  std::cout << "#collision layers: " << pLevel->getCollisionLayers()->size() << std::endl;
  std::cout << "#tilesets: " << pLevel->getTilesets()->size() << std::endl;
  return pLevel;
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
  assetsTag.append(pTilesetRoot->FirstChildElement()->Attribute("source"));
  std::cout << "adding Tileset " << assetsTag << " with ID " << pTilesetRoot->Attribute("name") << "\n";
  TextureManager::Instance()->load(
    assetsTag, // "assets/blocks1.png"
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
  ObjectLayer* pObjectLayer = new ObjectLayer();
  
  for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
    
    // e: <object>
    if (e->Value() == std::string("object")) {
      int x, y, width, height, numFrames, animSpeed = 0;
      std::string textureID;
      std::string type;
      // x, y: location on the whole big map
      e->Attribute("x", &x);
      e->Attribute("y", &y);
      // type: which Object class we must create
      type = e->Attribute("type");
      GameObject* pGameObject = GameObjectFactory::Instance()->create(type);
      for (TiXmlElement* properties = e->FirstChildElement(); properties != nullptr; properties = properties->NextSiblingElement()) {
        if (properties->Value() == std::string("properties")) {
          for (TiXmlElement* property = properties->FirstChildElement(); property != nullptr; property=property->NextSiblingElement()) {
            if (property->Value() == std::string("property")) {
              if (property->Attribute("name") == std::string("numFrames"))
                property->Attribute("value", &numFrames);
              else if (property->Attribute("name") == std::string("textureID")) 
                textureID = property->Attribute("value");
              else if (property->Attribute("name") == std::string("textureWidth"))
                property->Attribute("value", &width); // of the Texture image of Object
              else if (property->Attribute("name") == std::string("textureHeight"))
                property->Attribute("value", &height);
              else if (property->Attribute("name") == std::string("animSpeed")) 
                property->Attribute("value", &animSpeed);
            }
          }
        }
      }

      pGameObject->load(std::make_unique<LoaderParams>(x, y, width, height, textureID, numFrames, animSpeed));
      // set collision layers for every objects
      pGameObject->setCollisionLayers(pLevel->getCollisionLayers());
      pObjectLayer->getGameObjects()->push_back(pGameObject);
    }
  }
  pLayers->push_back(pObjectLayer);
}

// pTileElement:
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
void LevelParser::parseTileLayer(
  TiXmlElement* pTileElement, 
  std::vector<Layer*>* pLayers, 
  const std::vector<Tileset>* pTilesets, 
  std::vector<TileLayer*>* pCollisionLayers) 
{
  // m_width, m_height: [cell]
  TileLayer* pTileLayer = new TileLayer(m_tileSize, m_width, m_height, *pTilesets);
  bool collidable = false;
  std::vector<std::vector<int>> data; // final result 
  std::string decodedIDs;

  TiXmlElement* pDataNode;
  for (TiXmlElement* e = pTileElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
    
    if (e->Value() == std::string("properties")) { // collidable object
      for (TiXmlElement* property = e->FirstChildElement(); property != nullptr; property = property->NextSiblingElement()) {
        if (property->Value() == std::string("property")) {
          if (property->Attribute("name") == std::string("collidable")) {
            collidable = true;
          }            
        }
      }
    }

    if (e->Value() == std::string("data")) 
      pDataNode = e;
  }

  // pDataNode now points to <data/>
  for (TiXmlNode* e = pDataNode->FirstChild(); e != nullptr; e = e->NextSibling()) {
    TiXmlText* text = e->ToText();
    std::string t = text->Value();
    decodedIDs = base64_decode(t);
  }
  // uncompress zlib compression for tileIDs data
  uLongf sizeofids = m_width * m_height * sizeof(int); // size of whole Tilemap of ints
  std::vector<int> ids(m_width * m_height);
  uncompress((Bytef*)&ids[0], &sizeofids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size()); // first 2: unextracted; last 2: compressed
  // create buffer to store data in terms of vector<vector<int>>
  std::vector<int> layerRow(m_width);
  for (int j=0; j<m_height; j++) {
    data.push_back(layerRow);
  }
  // parsing tileIDs data into vector<vector<int>>
  for (int rows = 0; rows<m_height; rows++) {
    for (int cols = 0; cols < m_width; cols++) {
      data[rows][cols] = ids[rows*m_width + cols];
    }
  }
  pTileLayer->setTileIDs(data);
  // store <layer> with <property name="collidable".../> to a separate vector 
  if (collidable) {
    pCollisionLayers->push_back(pTileLayer);
  }
  // Note: 'pCollisionLayers' is a subset of 'pLayers'
  pLayers->push_back(pTileLayer);
}