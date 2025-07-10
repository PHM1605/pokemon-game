#pragma once 
#include <memory>
#include "GameObject.h"
#include "GameObjectFactory.h"

class MenuButton: public GameObject {
public:
  MenuButton();
  virtual ~MenuButton() {}

  virtual void load(std::unique_ptr<LoaderParams> const &pParams);
  virtual void render();
  virtual void update();

  virtual std::string type() { return "MenuButton"; }

private:
  enum button_state {
    NOT_CHOSEN = 0,
    CHOSEN = 1
  };
};

class MenuButtonCreator: public BaseCreator {
  GameObject* createGameObject() const {
    return new MenuButton();
  }
};