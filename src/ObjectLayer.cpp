#include "Camera.h"
#include "Game.h"
#include "ObjectLayer.h"

// ObjectLayer::ObjectLayer() {
//   m_bIsCollision = false;
// }

ObjectLayer::~ObjectLayer() {
  for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it!=m_gameObjects.end(); ++it) {
    delete (*it);
  }
  m_gameObjects.clear();
}

void ObjectLayer::update() {
  Vector2D camPos = Camera::Instance()->getPosition();
  
  if (!m_gameObjects.empty()) {
    for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();) {
      // if GameObject is within screen
      if ((*it)->getPosition().getX() <= camPos.getX() + Game::Instance()->getGameWidth()) {
        (*it)->setUpdating(true);
      } else {
        (*it)->setUpdating(false);
      }
    }    
  }

}

void ObjectLayer::render() {
  for (auto& gameObject: m_gameObjects) 
    gameObject->render();
}