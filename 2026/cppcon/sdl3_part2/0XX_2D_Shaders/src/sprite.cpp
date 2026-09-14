#include "sprite.hpp"

#include <iostream>
#include <string>

Sprite::Sprite(int order){
  mOrder = order;
  mPosition.x = 10;
  mPosition.y = 10;
  mPosition.w = 10;
  mPosition.h = 10;
}

Sprite::~Sprite(){
  std::cout << "Destroy texture\n";
  SDL_DestroyTexture(mTexture);
}

SDL_Texture* Sprite::LoadTexture(SDL_Renderer* renderer, std::string filepath, float x, float y, float w, float h){
  SDL_Texture* result;
  mPosition.x = x;
  mPosition.y = y;
  mPosition.w = w;
  mPosition.h = h;
  // A test surface for us to play with
  SDL_Surface* surface;

  if(filepath[filepath.size() - 3] == 'p'){
    std::cout << filepath[filepath.size() -3] << std::endl;
    surface = SDL_LoadPNG(filepath.c_str());
  }else{
    std::cout << filepath[filepath.size() -3] << std::endl;
    surface = SDL_LoadBMP(filepath.c_str());
  }

  result = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);

  if(result == nullptr){
    SDL_Log("Error loading texture: %s",filepath.c_str());
    SDL_Log("report: %s",SDL_GetError());
  }

  mTexture = result;
  return result;
}

void Sprite::Render(SDL_Renderer* renderer){
  SDL_RenderTexture(renderer, mTexture, nullptr, &mPosition);
}
