#include <iostream>
#include "Game.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "OverworldState.h"

bool MainMenuState::onEnter() {
  std::cout << "Entering MainMenuState\n";
  return true;
}

void MainMenuState::update() {
  if (m_bLoadingComplete) {
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) {
      Game::Instance()->getStateMachine()->changeState(new OverworldState());
    }
  }
}

void MainMenuState::render() {

}

bool MainMenuState::onExit() {
  std::cout << "exiting MainMenuState\n";
  return true;
}