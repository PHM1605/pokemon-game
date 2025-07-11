#include "Level.h"

Level::~Level() {
  for (auto& layer: m_layers) {
    delete layer;
  }
  m_layers.clear();

  for (auto& tileLayer: m_collisionLayers) {
    delete tileLayer;
  }
  m_collisionLayers.clear();
}

void Level::update() {
  for (int i=0; i<m_layers.size(); i++) {
    m_layers[i]->update();
  }
}

void Level::render() {
  for (int i=0; i<m_layers.size(); i++) {
    m_layers[i]->render();
  }
}