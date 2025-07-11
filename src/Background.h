#pragma once 
#include "GameObject.h"
#include "GameObjectFactory.h"

class Background: public GameObject {
public:
  virtual ~Background() {} 
  Background();

  virtual void load(std::unique_ptr<LoaderParams> pParams);
  virtual void render();
  virtual void update();
  virtual void clean();
  virtual std::string type() { return "Background"; }
};

class BackgroundCreator: public BaseCreator {
public:
  virtual GameObject* createGameObject() const {
    return new Background();
  }
};