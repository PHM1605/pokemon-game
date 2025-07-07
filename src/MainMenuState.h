#pragma once 
#include "GameState.h"

class MainMenuState: public GameState {
public:
  virtual ~MainMenuState() = default;

  virtual void update();
  virtual void render();

  virtual bool onEnter();
  virtual bool onExit();

  virtual std::string getStateID() const { return s_mainMenuID; }

private:
  static const std::string s_mainMenuID;
};