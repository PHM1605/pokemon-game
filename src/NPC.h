#pragma once 
#include <SDL2/SDL.h>
#include<string>
#include "GameObject.h"
#include "GameObjectFactory.h"

class NPC: public GameObject {
public:
  NPC(): GameObject() {}
  virtual ~NPC() {}

  

  bool load(SDL_Renderer* renderer, const std::string& file, int x, int y);
  void update();
  void render(SDL_Renderer* renderer);
  
  SDL_Rect getRect() const;

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