#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL3/SDL.h>
#include <string>
#include <memory>

struct Sprite{
  // Rendering state
  SDL_GPURenderState* mCustomRenderState  = nullptr;
//  std::weak_ptr<SDL_GPURenderState> mCustomRenderState  = nullptr;

  // Sprite Properties
  SDL_Texture* mTexture;
  SDL_FRect    mPosition;
  int          mOrder;
  // How will we render the sprite?
  std::string mRenderStateName;

  Sprite(SDL_Renderer* renderer, int order);
  ~Sprite();

  SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string filepath, float x, float y, float w, float h);

  void Render(SDL_Renderer* renderer);

  // Sets the name of the pipeline to lookup prior
  // to rendering.
  void SetRenderState(std::string pipeline);
};

#endif
