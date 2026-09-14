#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL3/SDL.h>
#include <string>

struct Sprite{
  SDL_Texture* mTexture;
  SDL_FRect    mPosition;
  int          mOrder;

  Sprite(int order);
  ~Sprite();

  SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string filepath, float x, float y, float w, float h);

  void Render(SDL_Renderer* renderer);
};

#endif
