#pragma once 
#include <SDL2/SDL.h>
#include <vector>

class GameState {
public:
  virtual void update() = 0;
  virtual void render() = 0;
  virtual bool onEnter() = 0;
  virtual void resume() {}
  virtual std::string getStateID() const = 0;

protected:
  GameState(): m_bLoadingComplete(false) {}
  virtual ~GameState() = default;
  bool m_bLoadingComplete;
};