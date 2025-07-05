#pragma once 
#include "GameState.h"
#include "Card.h"

class DuelState: public GameState {
public:
  DuelState();
  ~DuelState();
  
  void update() override;
  void render(SDL_Renderer* renderer) override;

private:
  Card m_card;
};