#pragma once 
#include "GameState.h"
#include "Card.h"

class DuelState: public GameState {
public:
  DuelState();
  ~DuelState();
  
  void update(const SDL_Event& e);
  void render(SDL_Renderer* renderer);

private:
  Card m_card;
};