#include "Camera.h"
#include "Game.h"
#include "ObjectLayer.h"

ObjectLayer::~ObjectLayer() {
  for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it!=m_gameObjects.end(); ++it) {
    delete (*it);
  }
  m_gameObjects.clear();
}

void ObjectLayer::update() {
  for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();) {
    // if GameObject is within screen
    Vector2D camPos = Camera::Instance()->getPosition();
    if ((*it)->getPosition().getX() <= camPos.getX() + Game::Instance()->getGameWidth()) {
      (*it)->update();
    }
  }
}

void ObjectLayer::render() {
  for (auto& gameObject: m_gameObjects) 
    gameObject->render();
}