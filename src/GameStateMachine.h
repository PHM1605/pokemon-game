#pragma once 
#include "GameState.h"
#include <memory>

class GameStateMachine {
public:
    GameStateMachine() = default;
    ~GameStateMachine() = default;

    void update();
    void render();
    void clean();

    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();

    std::vector<GameState*>& getGameStates();

private:
    std::vector<GameState*> m_gameStates;
};