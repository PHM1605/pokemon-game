#include "Game.h"
#include "InputHandler.h"

InputHandler* InputHandler::s_pInstance = nullptr;

InputHandler::InputHandler():
  m_keyStates(nullptr)
{}

InputHandler::~InputHandler() {
  delete m_keyStates;
}

void InputHandler::update() {
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_QUIT:
        Game::Instance()->quit(); // set m_bRunning flag to false
        break;
      case SDL_KEYDOWN:
        onKeyDown();
        break;
      case SDL_KEYUP:
        onKeyUp();
        break;
      default:
        break;
    }
  }
}

void InputHandler::onKeyDown() {
  m_keyStates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp() {
  m_keyStates = SDL_GetKeyboardState(0);
}

bool InputHandler::isKeyDown(SDL_Scancode key) const {
  if (m_keyStates != nullptr) {
    if (m_keyStates[key] == 1) {
      return true;
    } else 
      return false;
  }
  return false; // no key pressed
}