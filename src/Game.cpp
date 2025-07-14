#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Background.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "Npc.h"
#include "Player.h"
#include "TextureManager.h"
// #include "OverworldState.h"

Game* Game::s_pInstance = nullptr;

Game::Game():
  m_bRunning(false),
  m_pWindow(nullptr),
  m_pRenderer(nullptr),
  m_pGameStateMachine(nullptr)
{
  m_levelFiles.push_back("assets/level1.tmx");
  m_currentLevel = 1;
}

Game::~Game() {
  // they have been cleaned properly in onExit()
  m_pRenderer = nullptr;
  m_pWindow = nullptr;
}

bool Game::init(const char* title, int width, int height, bool fullscreen) {
  m_iGameWidth = width;
  m_iGameHeight = height;
  
  int flags = 0;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  if ( SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std:: cout << "SDL init success\n";
    m_pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (m_pWindow != 0) {
      std::cout << "window creation success\n";
      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
      if (m_pRenderer != 0) {
        std::cout << "renderer creation success\n";
        SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
      } else {
        std::cout << "renderer init fail\n";
        return false;
      }
    } else {
      std::cout << "window init fail\n";
      return false;
    }
  } else {
    std::cout << "SDL init fail\n";
    return false;
  }

  // register GameObjects' Creators
  GameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
  GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
  GameObjectFactory::Instance()->registerType("Background", new BackgroundCreator());
  GameObjectFactory::Instance()->registerType("Npc", new NpcCreator());

  m_pGameStateMachine = new GameStateMachine();
  m_pGameStateMachine->changeState(new MainMenuState());
  
  m_bRunning = true;
  return true;
}

void Game::update() {
  m_pGameStateMachine->update();
}

void Game::render() {
  SDL_RenderClear(m_pRenderer);
  m_pGameStateMachine->render();
  SDL_RenderPresent(m_pRenderer);
}

void Game::handleEvents() {
  InputHandler::Instance()->update();
}

void Game::clean() {
  // clean game state machine
  m_pGameStateMachine->clean();
  delete m_pGameStateMachine;
  m_pGameStateMachine = nullptr;
  // clean window and renderer
  SDL_DestroyRenderer(m_pRenderer);
  SDL_DestroyWindow(m_pWindow);
  SDL_Quit();
  // clear TextureMap
  TextureManager::Instance()->clean();
  // clean GameObjectFactory
  GameObjectFactory::Instance()->clean(); // clean m_objects
  // delete the Game Instance itself
  delete s_pInstance;
}