#include "CollisionManager.h"

bool CollisionManager::checkPlayerNpcCollision(Player* pPlayer, const std::vector<GameObject*> &objects) {
  SDL_Rect* pRect1 = new SDL_Rect();
  pRect1->x = pPlayer->getPosition().getX();
  pRect1->y = pPlayer->getPosition().getY();
  pRect1->w = pPlayer->getWidth();
  pRect1->h = pPlayer->getHeight();

  for (int i=0; i<objects.size(); i++) {
    // "not updating" means Object NOT within screen
    if (objects[i]->type() != std::string("Npc") || !objects[i]->getUpdating() ) {
      continue;
    }

    SDL_Rect* pRect2 = new SDL_Rect();
    pRect2->x = objects[i]->getPosition().getX();
    pRect2->y = objects[i]->getPosition().getY();
    pRect2->w = objects[i]->getWidth();
    pRect2->h = objects[i]->getHeight();

    if (SDL_HasIntersection(pRect1, pRect2)) {
      return true;
    } 
    delete pRect2;
  }
  delete pRect1;
  return false;
}