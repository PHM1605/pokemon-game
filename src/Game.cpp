#include "Game.h"
#include "MenuState.h"
// #include "OverworldState.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

Game* Game::s_pInstance = nullptr;

Game::Game():
  m_pWindow(nullptr),
  m_pRenderer(nullptr),
  m_bRunning(false),
  m_pGameStateMachine(nullptr)
{}

Game::~Game() {
  if (m_pWindow) {
    SDL_DestroyWindow(m_pWindow);
    m_pWindow = nullptr;
  }
  if(m_pRenderer) {
    SDL_DestroyRenderer(m_pRenderer);
    m_pRenderer = nullptr;
  }
  if (m_pGameStateMachine) {
    delete m_pGameStateMachine;
    m_pGameStateMachine = nullptr;
  }

  SDL_Quit();
  TTF_Quit();
}

void Game::changeState(std::shared_ptr<GameState> state) {
  m_currentState = state;
}

void Game::init(const char* title, int width, int height) {
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();
  m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
  changeState(std::make_shared<MenuState>());
  m_running = true;
}

void Game::run() {
  const int FPS = 60;
  const int frameDelay = 1000 / FPS; // milliseconds between 2 frames
  Uint32 frameStart;
  int frameTime; 

  SDL_Event e;
  while(m_running) {
    frameStart = SDL_GetTicks();

    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        m_running = false;
        std::cout << "CHECK1\n";
        std::cout << "TYPE OUTER2: " << e.type << std::endl;
      }
      
        
    }
    std::cout << "TYPE OUTER: " << e.type << std::endl;
    m_currentState->update(e);
    SDL_RenderClear(m_renderer);
    m_currentState->render(m_renderer);
    SDL_RenderPresent(m_renderer);

    // cap to 60FPS
    frameTime = SDL_GetTicks() - frameStart; 
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }
  }
}

void Game::clean() {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  IMG_Quit();
  SDL_Quit();
}