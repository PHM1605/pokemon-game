#pragma once 
#include <memory>
#include <vector>
#include "LoaderParams.h"
#include "TileLayer.h"
#include "Vector2D.h"

class GameObject {
public:
  virtual ~GameObject() {}

  virtual void load(std::unique_ptr<LoaderParams> pParams) = 0;
  virtual void render() = 0;
  virtual void update() = 0;
  
  virtual std::string type() = 0;

  Vector2D& getPosition() { return m_position; }
  void setCollisionLayers(std::vector<TileLayer*>* layers) { m_pCollisionLayers = layers; }

protected:
  GameObject():
    m_position(0,0), m_velocity(0,0), m_acceleration(0,0),
    m_width(0), m_height(0),
    m_currentRow(0), m_currentFrame(0), m_numFrames(0),
    m_bUpdating(false), // false if Object is out of Screen
    m_angle(0), m_alpha(255),
    m_textureID("")
  {}

  Vector2D m_position;
  Vector2D m_velocity;
  Vector2D m_acceleration;
  // size
  int m_width;
  int m_height;
  // animation
  int m_currentRow;
  int m_currentFrame;
  int m_numFrames;
  // moving left or right changes the Sprite flip direction
  bool m_bFlipped;
  // Object is within Screen or not 
  bool m_bUpdating;
  // additional infos
  double m_angle;
  int m_alpha;
  std::unique_ptr<LoaderParams> m_pParams;
  std::string m_textureID;
  std::vector<TileLayer*>* m_pCollisionLayers;
};