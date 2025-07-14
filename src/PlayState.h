#pragma once 
#include "GameState.h"
#include "Level.h"
#include "Npc.h"
#include "CollisionManager.h"
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
  // Npc m_opponent;

  bool m_duelTriggered = false;
  int m_duelStartTimer = 0; // frames
  int m_textX = -500; // text starting location

  std::vector<GameObject*> m_gameObjects;
  Level* pLevel;
  Player* m_pPlayer = nullptr;

  static const std::string s_playID;

  CollisionManager m_collisionManager;
};