#pragma once 
#include "GameState.h"
#include "Player.h"
#include "NPC.h"
#include <string>

class OverworldState: public GameState {
public:
  OverworldState();
  virtual ~OverworldState() {}
  virtual void update() override;
  virtual void render() override;

  virtual bool onEnter();
  virtual bool onExit();

  virtual std::string getStateID() const { return s_overworldID; }

private:
  Player m_player;
  NPC m_opponent;

  bool m_duelTriggered = false;
  int m_duelStartTimer = 0; // frames
  int m_textX = -500; // text starting location
  static const std::string s_overworldID;
};