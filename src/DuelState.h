#pragma once 
#include "GameState.h"
#include "Card.h"

class DuelState: public GameState {
public:
  DuelState();
  ~DuelState();
  
  void update(const SDL_Event& e) override;
  void render(SDL_Renderer* renderer) override;

private:
  Card m_card;
};