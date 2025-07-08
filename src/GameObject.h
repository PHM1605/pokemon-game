#pragma once 
#include "Vector2D.h"

class GameObject {
public:
  virtual ~GameObject() {}

protected:
  GameObject():
    m_position(0,0),
    m_width(0), m_height(0),
    m_currentRow(0), m_currentFrame(0), m_numFrames(0),
    m_textureID("")
  {}

  Vector2D m_position;
  // size
  int m_width;
  int m_height;
  // animation
  int m_currentRow;
  int m_currentFrame;
  int m_numFrames;

  std::string m_textureID;
};