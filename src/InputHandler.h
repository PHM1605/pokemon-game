#pragma once 
#include <SDL2/SDL.h>

class InputHandler {
public:
  // to make InputHandler a Singleton
  static InputHandler* Instance() {
    if (s_pInstance == nullptr) {
      s_pInstance = new InputHandler();
    }
    return s_pInstance;
  }

  void update();
  bool isKeyDown(SDL_Scancode key) const;
  

private:
  InputHandler();
  ~InputHandler();

  // handle keyboard events
  void onKeyDown();
  void onKeyUp();
  
  const Uint8* m_keyStates;

  // Singleton
  static InputHandler* s_pInstance;
};