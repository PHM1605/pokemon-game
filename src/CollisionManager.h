#pragma once 
#include <vector>
#include "Player.h"

class CollisionManager {
public:
  bool checkPlayerNpcCollision(Player* player, const std::vector<GameObject*>& objects);
};
