#include <SDL2/SDL_ttf.h>
#include <vector>
#include "Game.h"
#include "PlayState.h"
#include "StoryState.h"

// StoryState::StoryState() {
//   m_timer = 0;
// }

// void StoryState::update(const SDL_Event& e) {
  // m_timer++;
  // // wait ~5s (assuming 60fps)
  // if (m_timer>300) {
  //   Game::Instance()->changeState(std::make_shared<OverworldState>());
  // }
  // int currentLine = m_timer/180; // switch every 3s
  // if (currentLine >= story.size()) {
  //   Game::Instance()->changeState(std::make_shared<OverworldState>());
  // }
// }

// void StoryState::render(SDL_Renderer* renderer) {
  // SDL_SetRenderDrawColor(renderer, 0, 0 ,0, 255);
  // SDL_RenderClear(renderer);
  // static TTF_Font* font = TTF_OpenFont("assets/arial.ttf", 24);
  // std::vector<std::string> story = {
  //   "Long ago, duelists ruled the world...",
  //   "But a shadowy force corrupted the cards...",
  //   "You must duel to restore balance!"
  // };

  // if (font) {
  //   SDL_Color white = {255, 255, 255};
  //   SDL_Surface* surf = TTF_RenderText_Solid(font, "Long ago, duelists ruled the world...", white);
  //   SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
  //   SDL_Rect dst = {100, 300, surf->w, surf->h};
  //   SDL_RenderCopy(renderer, tex, nullptr, &dst);
  //   SDL_FreeSurface(surf);
  //   SDL_DestroyTexture(tex);
  // }

// }