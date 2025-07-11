#pragma once 
#include <SDL2/SDL.h>
#include<string>
#include "GameObject.h"
#include "GameObjectFactory.h"

class NPC: public GameObject {
public:
  NPC(): GameObject() {}
  virtual ~NPC() {}

  

  void load(std::unique_ptr<LoaderParams> const pParams);
  void update();
  void render();
  
  // SDL_Rect getRect() const;

  virtual std::string type() { return "NPC"; }

private:
  SDL_Texture* m_texture = nullptr;
  SDL_Rect m_rect;
};

class NPCCreator: public BaseCreator {
  GameObject* createGameObject() const {
    return new NPC();
  }
};