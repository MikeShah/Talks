#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SDL3/SDL.h>
#include <vector>
#include "resourcemanager.hpp"
#include "sprite.hpp"


// Holds all of our objects
struct GameState{

  // Objects in our scene.
  std::vector<Sprite*> mSprites;
  // Hold onto my Resource Manager
  ResourceManager*    mResourceManager;

  GameState(SDL_Renderer* renderer);

  ~GameState();

  // Render -- note this is the 'comically underpowered version'
  //           We might want to render from a specific 'camera' 
  //           or provide a filtering function here.
  void Render(SDL_Renderer* renderer);
};

#endif
