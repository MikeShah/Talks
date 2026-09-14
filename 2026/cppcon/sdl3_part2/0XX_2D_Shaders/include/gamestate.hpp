#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SDL3/SDL.h>

// Holds all of our objects
struct GameState{
  // Rendering state
  SDL_GPURenderState* mCustomRenderState  = nullptr;
  SDL_GPUShader*      mGPUShader          = nullptr;

  // Objects
  SDL_Texture*  mTexture[100];
  bool          mActiveObjects[100];


  GameState(SDL_Renderer* renderer);

  ~GameState();

  void Render(SDL_Renderer* renderer);
};

#endif
