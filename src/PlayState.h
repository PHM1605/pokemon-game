#pragma once 
#include "GameState.h"
#include "Level.h"
#include "NPC.h"
#include "Player.h"
#include <string>

class PlayState: public GameState {
public:
  PlayState();
  virtual ~PlayState() {}

  virtual void load();
  virtual void update();
  virtual void render();  
  virtual void clean();

  virtual std::string getStateID() const { return s_playID; }
  Player* getPlayer() { return m_pPlayer; }

private:
  // Player m_player;
  // NPC m_opponent;

  bool m_duelTriggered = false;
  int m_duelStartTimer = 0; // frames
  int m_textX = -500; // text starting location

  std::vector<GameObject*> m_gameObjects;
  Level* pLevel;
  Player* m_pPlayer = nullptr;

  static const std::string s_playID;
};