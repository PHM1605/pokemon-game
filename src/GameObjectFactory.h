#pragma once 
#include <map>
#include <string>
#include "GameObject.h"


class BaseCreator {
public:
  virtual GameObject* createGameObject() const = 0;
  virtual ~BaseCreator() {}
};

class GameObjectFactory {
public:
  // to make GameObjectFactory a Singleton
  static GameObjectFactory* Instance() {
    if (pInstance == nullptr){
      pInstance = new GameObjectFactory;
    }
    return pInstance;
  }

  void clean();

  bool registerType(std::string typeID, BaseCreator* pCreator); // add a Creator to the map
  GameObject* create(std::string typeID); // ask a Creator to create its Object

private: 
  GameObjectFactory() {}
  ~GameObjectFactory() {}

  std::map<std::string, BaseCreator*> m_creators;
  static GameObjectFactory* pInstance;
};