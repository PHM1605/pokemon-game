#include <iostream>
#include "DuelState.h"
#include "Game.h"

const std::string DuelState::s_duelStateID = "DUEL";

void DuelState::update() {}

void DuelState::render() {
  std::cout << "Rendering " << s_duelStateID << "\n";
}