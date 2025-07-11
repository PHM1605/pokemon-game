#include "GameStateMachine.h"
#include <string>
#include <iostream>

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
        gameState->clean();
        delete gameState;
    }
    m_gameStates.clear();
}

std::vector<GameState*>& GameStateMachine::getGameStates() { 
    return m_gameStates; 
}

void GameStateMachine::popState() {
    if (!m_gameStates.empty()) {
        m_gameStates.back()->load();
        m_gameStates.pop_back();
    }
}

void GameStateMachine::pushState(GameState* pState) {
    m_gameStates.push_back(pState);
    m_gameStates.back()->load();
}

void GameStateMachine::changeState(GameState* pState) {
    if (!m_gameStates.empty()) {
        if (m_gameStates.back()->getStateID() == pState->getStateID())
            return; // do nothing
        m_gameStates.pop_back();
    }
    pState->load();
    m_gameStates.push_back(pState);
}

