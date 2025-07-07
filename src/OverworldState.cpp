#include <SDL2/SDL_ttf.h>
#include "DuelState.h"
#include "Game.h"
#include "OverworldState.h"
#include <iostream>

OverworldState::OverworldState() {
  SDL_Renderer* r = Game::Instance()->getRenderer();
  m_player.load(r, "assets/player.png", 200, 300); // position on map (200,300)
  m_opponent.load(r, "assets/opponent.png", 600, 300);
}

void OverworldState::update(const SDL_Event& e) {
  if (m_duelTriggered) {
    m_duelStartTimer++;
    // animate text sliding in
    if (m_textX < 400)
      m_textX += 20;
    if (m_duelStartTimer > 120) {
      Game::Instance()->changeState(std::make_shared<DuelState>());
    }
    return;
  }

  const Uint8* keystate = SDL_GetKeyboardState(nullptr);
  m_player.handleInput(keystate);
  m_player.update();

  SDL_Rect playerRect = m_player.getRect();
  SDL_Rect opponentRect = m_opponent.getRect();

  // Collision check
  if (SDL_HasIntersection(&playerRect, &opponentRect)) {
    m_duelTriggered = true;
    m_duelStartTimer = 0;
    m_textX = -500; // reset animation
  }
}

void OverworldState::render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255);
  SDL_RenderClear(renderer);
  m_player.render(renderer);
  m_opponent.render(renderer);

  if (m_duelTriggered) {
    // Show "DUEL START!" overlay
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_Rect overlay = {0, 0, 1280, 720}; 
    SDL_RenderFillRect(renderer, &overlay);
    // Draw text
    static TTF_Font* font = TTF_OpenFont("assets/fonts/monogram.ttf", 48);
    if (font) {
      SDL_Color white = {255, 255, 255};
      SDL_Surface* surface = TTF_RenderText_Solid(font, "DUEL START!", white);
      SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
      SDL_Rect dst = {m_textX, 320, surface->w, surface->h};
      SDL_RenderCopy(renderer, texture, nullptr, &dst);
      SDL_FreeSurface(surface);
      SDL_DestroyTexture(texture);
    } else {
      std::cerr << "TTF_OpenFont failed: " << TTF_GetError() << "\n";
    }
  }
}