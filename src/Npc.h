#pragma once 
#include <SDL2/SDL.h>
#include<string>
#include "GameObject.h"
#include "GameObjectFactory.h"

class Npc: public GameObject {
public:
  Npc(): GameObject() {}
  virtual ~Npc() {}

  

  void load(std::unique_ptr<LoaderParams> const pParams);
  void update();
  void render();
  
  // SDL_Rect getRect() const;

  virtual std::string type() { return "Npc"; }

private:
  SDL_Texture* m_texture = nullptr;
  SDL_Rect m_rect;
};

class NpcCreator: public BaseCreator {
  GameObject* createGameObject() const {
    return new Npc();
  }
};