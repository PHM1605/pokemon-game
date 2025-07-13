#pragma once 

class Level;

class Layer {
public:
  virtual ~Layer() {}
  virtual void render() = 0;
  virtual void update() = 0; // do nothing in Game, we don't scroll map, but use Camera

};