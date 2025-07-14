#pragma once 
#include "GameState.h"

class DuelState: public GameState {
public:
  DuelState() {}
  ~DuelState() {}
  
  virtual void load() {}
  virtual void update();
  virtual void render();
  void clean() {}

  virtual std::string getStateID() const { return s_duelStateID; }

private:
  static const std::string s_duelStateID;
};