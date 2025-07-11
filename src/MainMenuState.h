#pragma once 
#include "GameObject.h"
#include "GameState.h"

class MainMenuState: public GameState {
public:
  virtual ~MainMenuState() = default;

  virtual void load();
  virtual void update();
  virtual void render();
  virtual void clean();

  virtual std::string getStateID() const { return s_mainMenuID; }

private:
  static const std::string s_mainMenuID; // = stateID (set in game.xml file)
  std::vector<GameObject*> m_gameObjects;
};