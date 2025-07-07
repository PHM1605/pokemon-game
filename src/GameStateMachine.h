#pragma once 
#include "GameState.h"
#include <memory>

class GameStateMachine {
public:
    GameStateMachine() = default;
    ~GameStateMachine() = default;

    void update();
    void render();

    void pushState(std::unique_ptr<GameState> pState);
    void changeState(std::unique_ptr<GameState> pState);
    void popState();

    std::vector<std::unique_ptr<GameState>>& getGameStates();

private:
    std::vector<std::unique_ptr<GameState>> m_gameStates;
};