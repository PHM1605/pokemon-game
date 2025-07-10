#include <iostream>
#include "GameObjectFactory.h"

GameObjectFactory* GameObjectFactory::pInstance = nullptr;

bool GameObjectFactory::registerType(std::string typeID, BaseCreator* pCreator) {
  std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
  // if Creator of typeID exists, do nothing
  if (it != m_creators.end())
    delete pCreator;
  m_creators[typeID] = pCreator;
  return true;
}

GameObject* GameObjectFactory::create(std::string typeID) {
  std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
  if (it == m_creators.end()) {
    std::cout << "could not find type: " << typeID << "\n";
    return nullptr;
  }
  BaseCreator* pCreator = (*it).second;
  return pCreator->createGameObject();
}

void GameObjectFactory::clean() {
  for (auto& pair: m_creators) {
    delete pair.second;
  }
  m_creators.clear();
}
