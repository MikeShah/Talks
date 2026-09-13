#ifndef GAMEAPPLICATION_HPP
#define GAMEAPPLICATION_HPP
#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>
#include "shader.hpp"

struct EnvironmentUniforms {
  float screen_width;
  float screen_height;
  float time;
  float padding; // Pad to maintain a 16-byte boundary (4 floats * 4 bytes = 16)
};

/*
  // Reflection()
  void Reflect(){
    // Reflect on the Greet struct type
    constexpr auto type_refl = ^^GameState;
    
    // Print the name of the reflected type
    std::cout << "Type name: " << std::meta::name_of(type_refl) << '\n';
    
    // Iterate and inspect non-static data members
    template for (constexpr auto member : std::meta::non_static_data_members_of(^^Greet)) {
        std::cout << "Member name: " << std::meta::name_of(member) << '\n';
    }
  }
*/

// Holds all of our objects
struct GameState{
  // Rendering state
  SDL_GPURenderState* mCustomRenderState  = nullptr;
  SDL_GPUShader*      mGPUShader          = nullptr;

  // Objects
  SDL_Texture*  mTexture[100];
  bool          mActiveObjects[100];


  GameState(SDL_Renderer* renderer){
    // Load the shader code into a buffer of bytes
    mGPUShader = LoadShader(renderer,"./my_frag_shader.frag.spv");
    SDL_GPURenderStateCreateInfo state_info;
    SDL_zero(state_info); // zero out the 'state_info'
    state_info.fragment_shader = mGPUShader;
    mCustomRenderState = SDL_CreateGPURenderState(renderer, &state_info);

    // A test surface for us to play with
    SDL_Surface* surface = SDL_LoadBMP("./assets/character.bmp");

    mTexture[0] = SDL_CreateTextureFromSurface(renderer, surface);
    //    SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);

    SDL_DestroySurface(surface);
  }

  ~GameState(){
    for(int i=0; i < 100; i++){
      SDL_DestroyTexture(mTexture[i]);
    }
    SDL_DestroyGPURenderState(mCustomRenderState);
    //    SDL_ReleaseGPUShader(device, shader); // TODO
  }

  void Render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
    // Draw a texture
    static SDL_FRect dst_rect{.x = 50, .y = 25, .w = 48, .h = 56 };
    dst_rect.x += 0.1f;

    // STAGE 2: Populate and Modify Data structures
    EnvironmentUniforms env_data = {
      .screen_width = 640.0f,
      .screen_height = 480.0f,
      .time = (float)SDL_GetTicks() / 1000.0f
    };
    // STAGE 3: Inject parameters using SDL_SetGPURenderStateFragmentUniforms
    // Pass Environment data to binding uniform Slot 0
    if (!SDL_SetGPURenderStateFragmentUniforms(mCustomRenderState, 0, &env_data, sizeof(env_data))) {
      SDL_Log("Failed to push data to Fragment Uniform Slot 0: %s", SDL_GetError());
    }

    for(int i=0; i < 100; i++){
      if(mTexture[i] != nullptr){
        // Pass in our custom renderer
        SDL_SetGPURenderState(renderer, mCustomRenderState);
        SDL_RenderTexture(renderer, mTexture[i], nullptr, &dst_rect);
        /// Back to the default renderer
        SDL_SetGPURenderState(renderer, nullptr);
        // For debugging purposes render a rectangle where we think our shape should be.
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderRect(renderer, &dst_rect);
      }
    }

    // ... more drawing operations
    SDL_RenderPresent(renderer);
  }
};

struct GameApplication{
  SDL_Window*         mWindow;
  SDL_Renderer*       mRenderer;

  // Hold onto the gamestate
  GameState*          mGameState;

  // For my application to run indefinitely
  bool mRunning                           = true;
  bool mFullScreen                        = true;

  // Constructor
  GameApplication(const char* title);
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
