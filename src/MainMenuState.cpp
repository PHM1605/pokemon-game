#include <iostream>
#include "Game.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "StateParser.h"

const std::string MainMenuState::s_mainMenuID = "MAINMENU";

void MainMenuState::load() {
  std::cout << "Entering MainMenuState\n";
  StateParser stateParser;
  stateParser.parseState("assets/game.xml", s_mainMenuID, &m_gameObjects, &m_textureIDList);
  m_bLoadingComplete = true;
}

void MainMenuState::update() {
  if (m_bLoadingComplete) {
    for (int i=0; i<m_gameObjects.size(); i++) {
      m_gameObjects[i]->update();
    }
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) {
      Game::Instance()->getStateMachine()->changeState(new PlayState());
    }
  }
}

void MainMenuState::render() {

}

void MainMenuState::clean() {
  std::cout << "exiting MainMenuState\n";
  if (m_bLoadingComplete && !m_gameObjects.empty()) {
    for (auto pGameObject: m_gameObjects) {
      delete pGameObject;
    }
  }
  m_gameObjects.clear();
}