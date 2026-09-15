#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SDL3/SDL.h>
#include <vector>
#include "sprite.hpp"


// Holds all of our objects
struct GameState{

  // Objects in our scene.
  std::vector<Sprite*> mSprites;

  GameState(SDL_Renderer* renderer);

  ~GameState();

  void Render(SDL_Renderer* renderer, SDL_GPURenderState* renderState);
};

#endif
