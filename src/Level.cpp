#include "Level.h"

Level::~Level() {
  // we only need to clean m_layers, as it includes m_collisionLayers already
  for (auto& layer: m_layers) {
    delete layer;
  }
  m_layers.clear();
}

void Level::update() {
  for (int i=0; i<m_layers.size(); i++) {
    m_layers[i]->update();
  }
}
void Level::render() {
  for (int i=0; i<m_layers.size(); i++) {
    // if (!m_layers[i]->getIsCollision())
      m_layers[i]->render();
  }
}

ObjectLayer* Level::getObjectLayer() {
  for (auto layer: m_layers) {
    if (auto pObjectLayer = dynamic_cast<ObjectLayer*>(layer)) {
      return pObjectLayer;
    }
  }
  return nullptr;
}