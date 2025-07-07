#include "GameStateMachine.h"

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

void GameStateMachine::pushState(std::unique_ptr<GameState> pState) {
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(std::unique_ptr<GameState> pState) {
    if (!m_gameStates.empty()) {
        if (m_gameStates.back()->getStateID() == pState->getStateID())
            return; // do nothing
        m_gameStates.pop_back();
    }
    pState->onEnter();
    m_gameStates.push_back(pState);
}

std::vector<std::unique_ptr<GameState>>& GameStateMachine::getGameStates() { 
    return m_gameStates; 
}

void GameStateMachine::popState() {
    if (!m_gameStates.empty()) {
        m_gameStates.pop_back();
    }
    m_gameStates.back()->resume();
}

