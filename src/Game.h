#pragma once 
#include <SDL2/SDL.h>
#include <memory> // for shared_ptr
#include "GameStateMachine.h"

class GameState;

class Game {
public:
  // to make Game a Singleton
  static Game* Instance() {
    if (s_pInstance == nullptr) {
      s_pInstance = new Game();
      return s_pInstance;
    }
    return s_pInstance;
  }

  void init(const char* title, int width, int height);
  void update();
  void render();
  void handleEvents();
  void clean();

  SDL_Renderer* getRenderer() const { return m_pRenderer; }
  SDL_Window* getWindow() const { return m_pWindow; }
  std::unique_ptr<GameStateMachine>& getStateMachine() { return m_pGameStateMachine; }
  void quit() { m_bRunning = false; }
  bool running() { return m_bRunning; }

private:
  Game();
  ~Game();

  bool m_bRunning = false;
  SDL_Window* m_pWindow = nullptr;
  SDL_Renderer* m_pRenderer = nullptr;
  std::unique_ptr<GameStateMachine> m_pGameStateMachine;
  int m_iGameWidth;
  int m_iGameHeight;
  
  static Game* s_pInstance;
  std::shared_ptr<GameState> m_currentState;
};