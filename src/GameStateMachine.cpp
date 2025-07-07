#include "GameStateMachine.h"
#include <string>

void GameStateMachine::update() {
    if (!m_gameStates.empty()) {
        m_gameStates.back()->update();
    }
}

void GameStateMachine::render() {
    if (!m_gameStates.empty()) {
        m_gameStates.back()->render();
    }
}

void GameStateMachine::clean() {
    for (auto gameState: m_gameStates) {
        gameState->onExit();
        delete gameState;
    }
    m_gameStates.clear();
}

std::vector<GameState*>& GameStateMachine::getGameStates() { 
    return m_gameStates; 
}

void GameStateMachine::popState() {
    if (!m_gameStates.empty()) {
        m_gameStates.back()->onExit();
        m_gameStates.pop_back();
    }
    m_gameStates.back()->resume(); // do nothing
}

void GameStateMachine::pushState(GameState* pState) {
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState* pState) {
    if (!m_gameStates.empty()) {
        if (m_gameStates.back()->getStateID() == pState->getStateID())
            return; // do nothing
        m_gameStates.pop_back();
    }
    pState->onEnter();
    m_gameStates.push_back(pState);
}


void GameStateMachine::popState() {
    if (!m_gameStates.empty()) {
        m_gameStates.back()->onExit();
        m_gameStates.pop_back();
    }
    m_gameStates.back()->resume(); // do nothing
}

