#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SDL3/SDL.h>
#include <vector>
#include "resourcemanager.hpp"
#include "sprite.hpp"

// One big struture to send every frame
struct GameStateUniforms{
  float screen_width;
  float screen_height;
  float mouseX;
  float mouseY;
  float time;
  float color_scale; 
  float alpha;
  float padding;
};

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

  // Data passed in here once per-frame that is shared across all shaders.
  GameStateUniforms mGameStateUniforms;
};

#endif
