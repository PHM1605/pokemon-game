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

  bool init(const char* title, int width, int height, bool fullscreen);
  void update();
  void render();
  void handleEvents();
  void clean();

  SDL_Renderer* getRenderer() const { return m_pRenderer; }
  SDL_Window* getWindow() const { return m_pWindow; }
  GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

  bool running() { return m_bRunning; }
  void quit() { m_bRunning = false; }

  int getGameWidth() const { return m_iGameWidth; }
  int getGameHeight() const { return m_iGameHeight; }
  
private:
  Game();
  ~Game() { delete s_pInstance; }

  bool m_bRunning = false;
  SDL_Window* m_pWindow = nullptr;
  SDL_Renderer* m_pRenderer = nullptr;
  GameStateMachine* m_pGameStateMachine;
  int m_iGameWidth;
  int m_iGameHeight;
  
  static Game* s_pInstance;
  std::shared_ptr<GameState> m_currentState;
};