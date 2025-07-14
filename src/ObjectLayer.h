#pragma once 
#include <vector>
#include "Layer.h"

class GameObject;

class ObjectLayer: public Layer {
public:
  // ObjectLayer();
  virtual ~ObjectLayer();

  virtual void update();
  virtual void render();

  std::vector<GameObject*>* getGameObjects() { return &m_gameObjects; }

private:
  std::vector<GameObject*> m_gameObjects;
  bool m_bIsCollision;
};