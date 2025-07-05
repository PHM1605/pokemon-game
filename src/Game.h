#pragma once 
#include <SDL2/SDL.h>
#include <memory> // for shared_ptr

class GameState;

class Game {
public:
  // to make Game a Singleton
  static Game* Instance() {
    if (instance == nullptr) {
      instance = new Game();
      return instance;
    }
    return instance;
  }

  void init(const char* title, int width, int height);
  void run();
  void clean();

  SDL_Renderer* getRenderer() const { return m_renderer; }
  void changeState(std::shared_ptr<GameState> state);

private:
  Game() = default;
  SDL_Window* m_window = nullptr;
  SDL_Renderer* m_renderer = nullptr;
  bool m_running = false;
  static Game* instance;
  std::shared_ptr<GameState> m_currentState;
};