#ifndef GAMEAPPLICATION_HPP
#define GAMEAPPLICATION_HPP
#include <SDL3/SDL.h>

#include "shader.hpp"
#include "gamestate.hpp"
#include "resourcemanager.hpp"


struct GameApplication{
  SDL_Window*         mWindow;
  SDL_Renderer*       mRenderer;

  // Hold onto the gamestate
  GameState*          mGameState;

  // Hold onto my Resource Manager
  ResourceManager*    mResourceManager;

  // For my application to run indefinitely
  bool mRunning                           = true;
  bool mFullScreen                        = true;

  // Constructor
  GameApplication(const char* title, int argc, char* argv[]);
  // Destructor
  ~GameApplication();
  // Handle input events from I/O or networking devices
  void Input();
  void Update();
  void Render();
  // Advances our loop one iteration (calling input/update/render)
  // It's very easy to add a breakpoint
  void Tick();
  // Calls 'Tick' in an infinite loop
  void MainLoop();
};

#endif
