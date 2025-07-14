#pragma once 
#include <vector>
#include "Player.h"

class CollisionManager {
public:
  GameObject* checkPlayerNpcCollision(
    Player* player, 
    const std::vector<GameObject*>& objects);
};
