#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include "GameObjectFactory.h"
#include "Level.h"

class Player: public GameObject {
public:
  Player();
  virtual ~Player() {}

  virtual std::string type() { return "Player"; }
  void load(std::unique_ptr<LoaderParams> pParams);
  void handleInput();
  void update();
  void render();
  void handleMovement(Vector2D velocity);
  bool checkCollideTile(Vector2D newPos);
  
  void setLevel(Level* pLevel) { m_pLevel = pLevel; }
  Level* getLevel() { return m_pLevel; }

private:
  SDL_Texture* m_texture = nullptr;
  int m_speed = 4;

  bool m_bMoveRight;
  bool m_bMoveLeft;
  bool m_bMoveUp;
  bool m_bMoveDown;
  Level* m_pLevel;
};

class PlayerCreator: public BaseCreator {
  GameObject* createGameObject() const {
    return new Player();
  }
};