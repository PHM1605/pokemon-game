#pragma once 
#include "GameState.h"
#include "Player.h"
#include "NPC.h"
#include <string>

class OverworldState: public GameState {
public:
  OverworldState();
  void update(const SDL_Event& e) override;
  void render(SDL_Renderer* renderer) override;

private:
  Player m_player;
  NPC m_opponent;

  bool m_duelTriggered = false;
  int m_duelStartTimer = 0; // frames
  int m_textX = -500; // text starting location
};