#include "DuelState.h"
#include "Game.h"

DuelState::DuelState() {
  // position of Card on screen is 500, 300
  m_card.load("assets/bewd.png", 500, 300, 150, 200);
}

DuelState:: ~DuelState() {}

void DuelState::update(const SDL_Event &e) {}

void DuelState::render(SDL_Renderer* renderer) {
  m_card.render(renderer);
}