#include <SDL3/SDL.h>
#include <string>
#include <vector>
#include <cassert>

#include "gameapplication.hpp"

// Constructor
GameApplication::GameApplication(const char* title, int argc, char* argv[]){
  SDL_Init(SDL_INIT_VIDEO);
  mWindow = SDL_CreateWindow(title, 640, 480,SDL_WINDOW_RESIZABLE);
  mRenderer = SDL_CreateGPURenderer(nullptr, mWindow);
  if(mRenderer==  nullptr){
    assert(0 && "Not able to create HW accelerated renderer");
  }

  SDL_Log("Renderer: %s",SDL_GetRendererName(mRenderer));
  SDL_Log("Available renderer drivers:");
  for (int i = 0; i < SDL_GetNumRenderDrivers(); i++) {
    SDL_Log("%d. %s", i + 1, SDL_GetRenderDriver(i));
  }
  SDL_SetRenderLogicalPresentation(mRenderer, 640, 480,SDL_LOGICAL_PRESENTATION_LETTERBOX);

  // Create a new Game State once SDL3 is initialized
  mGameState = new GameState(mRenderer);
}
// Destructor
GameApplication::~GameApplication(){
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);
  SDL_Quit();
}

// Advances our loop one iteration
// It's very easy to add a breakpoint
void GameApplication::Tick(){
  Input();
  Update();
  Render();
}

// Handle input events from I/O or networking devices
void GameApplication::Input(){
  SDL_Event event;

  while(SDL_PollEvent(&event)){
    // Quit event
    if(event.type == SDL_EVENT_QUIT){
      mRunning=false;
    }
    else if(event.type == SDL_EVENT_KEY_DOWN){
      SDL_Log("a key was pressed: %d",event.key.key);
      if(event.key.key == SDLK_F11){
        mFullScreen = !mFullScreen;
        SDL_SetWindowFullscreen(mWindow, mFullScreen );
      }
    }
    else if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
      if(event.button.button == SDL_BUTTON_LEFT){
        SDL_Log("left button clicked %d",event.button.button);
      }  
      if(event.button.button == SDL_BUTTON_MIDDLE){
        SDL_Log("middle button clicked %d",event.button.button);
      }  
      if(event.button.button == SDL_BUTTON_RIGHT){
        SDL_Log("right button clicked %d",event.button.button);
      }  
      SDL_Log("Clicks: %d",event.button.clicks);
    }
  }

  float x,y;
  // Get the 'local' within current mWindow mouse position
  SDL_MouseButtonFlags mouse = SDL_GetMouseState(&x, &y);
  // Get mouse position outside mWindow, across multiple monitors.
  //SDL_MouseButtonFlags mouse = SDL_GetGlobalMouseState(&x, &y);
  // SDL_Log("x,y: %f,%f",x,y);

  // Application/Game logic
  // ...
}

void GameApplication::Update(){
}

void GameApplication::Render(){
  if(mGameState != nullptr){
    mGameState->Render(mRenderer);
  }
}

// Main application loop
void GameApplication::MainLoop(){
  Uint64 fps=0; // Number of frames per second
  Uint64 lastTime = 0;

  // Our infinite loop
  while(mRunning){
    Uint64 currentTick = SDL_GetTicks();
    Tick();
    SDL_Delay(16);
    fps++;
    // Per frame calculation of elapsed time
    Uint64 deltaTime = SDL_GetTicks() - currentTick;

    // FPS Calculation
    if(currentTick > lastTime + 1000){
      lastTime = currentTick; 
      std::string title;
      title += "Mike's SDL3 Tutorials - FPS " + std::to_string(fps);
      SDL_SetWindowTitle(mWindow,title.c_str());
      fps=0;
    }
  }
}
