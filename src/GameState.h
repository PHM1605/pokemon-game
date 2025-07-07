#pragma once 
#include <SDL2/SDL.h>
#include <vector>

class GameState {
public:
  virtual ~GameState() = default;
  virtual void update() = 0;
  virtual void render() = 0;
  virtual void resume() {}

  virtual bool onEnter() = 0;
  virtual bool onExit() = 0;
  
  virtual std::string getStateID() const = 0;

protected:
  GameState(): m_bLoadingComplete(false) {}
  bool m_bLoadingComplete; // usually set to 'true' at the end of onEnter()
  
};