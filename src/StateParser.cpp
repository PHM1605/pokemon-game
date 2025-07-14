#include "Game.h"
#include "GameObjectFactory.h"
#include "StateParser.h"
#include "TextureManager.h"

// parse file "game.xml"
// <MAINMENU>
//   <TEXTURES>
//     <texture filename="assets/main-menu-screen.png" ID="mainmenuscreen"/>
//     <texture filename="assets/press-start.png" ID="newgamebutton" />
//   </TEXTURES>
//   <OBJECTS>
//     <object type="MenuButton" x="400" y="400" width="400" height="100" textureID="newgamebutton" numFrames="0" />
//   </OBJECTS>
// </MAINMENU>

bool StateParser::parseState(const char* stateFile, std::string stateID, std::vector<GameObject*>* pObjects, std::vector<std::string>* pTextureIDs) {
  TiXmlDocument xmlDoc;
  if (!xmlDoc.LoadFile(stateFile)) {
    std::cerr << xmlDoc.ErrorDesc() << "\n";
    return false;
  }
  TiXmlElement* pRoot = xmlDoc.RootElement(); // <States>

  // Get <MAINMENU> tag
  TiXmlElement* pStateRoot = nullptr;
  for (TiXmlElement* e = pRoot->FirstChildElement(); e!=NULL; e=e->NextSiblingElement()) {
    if (e->Value() == stateID) { // <MAINMENU>
      pStateRoot = e;
      break;
    }
  }

  // Get <TEXTURES> tag
  TiXmlElement* pTextureRoot = nullptr;
  for (TiXmlElement* e = pStateRoot->FirstChildElement(); e!=NULL; e=e->NextSiblingElement()) {
    if (e->Value() == std::string("TEXTURES")) {
      pTextureRoot = e; // <TEXTURES>
      break;
    }
  }
  parseTextures(pTextureRoot, pTextureIDs);

  // Get <OBJECTS> tag
  TiXmlElement* pObjectRoot = nullptr;
  for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
    if (e->Value() == std::string("OBJECTS")) {
      pObjectRoot = e;
      break;
    }
  }
  parseObjects(pObjectRoot, pObjects);
  return true;
}

// pStateRoot: <TEXTURES> tag
// pTextureIDs: store parsing Textures result
void StateParser::parseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs) {
  for (TiXmlElement* e = pStateRoot->FirstChildElement(); e!=nullptr; e=e->NextSiblingElement()) {
    // e: <texture filename="assets/main-menu-screen.png" ID="mainmenuscreen"/>
    std::string filenameAttribute = e->Attribute("filename");
    std::string idAttribute = e->Attribute("ID");
    pTextureIDs->push_back(idAttribute);
    TextureManager::Instance()->load(filenameAttribute, idAttribute, Game::Instance()->getRenderer());
  }
}

// pStateRoot: <OBJECTS> tag
// pObjects: store parsing result
void StateParser::parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*>* pObjects) {
  for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
    int x, y, width, height, numFrames, animSpeed;
    std::string textureID;
    // e: <object type="MenuButton" x="400" y="400" width="400" height="100" textureID="newgamebutton" numFrames="0" />
    e->Attribute("x", &x);
    e->Attribute("y", &y);
    e->Attribute("width", &width);
    e->Attribute("height", &height);
    e->Attribute("animSpeed", &animSpeed);
    textureID = e->Attribute("textureID");
    
    GameObject* pGameObject = GameObjectFactory::Instance()->create(e->Attribute("type"));
    pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames, animSpeed)));
    pObjects->push_back(pGameObject);
  }
}