#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include "GameObjectFactory.h"

class Player: public GameObject {
public:
  Player();
  virtual ~Player() {}

  virtual std::string type() { return "Player"; }
  void load(std::unique_ptr<LoaderParams> pParams);
  void handleInput(const Uint8* keyState);
  void update();
  void render();
  SDL_Rect getRect() const;
  

private:
  SDL_Texture* m_texture = nullptr;
  SDL_Rect m_rect;
  int m_speed = 4;
};

class PlayerCreator: public BaseCreator {
  GameObject* createGameObject() const {
    return new Player();
  }
};