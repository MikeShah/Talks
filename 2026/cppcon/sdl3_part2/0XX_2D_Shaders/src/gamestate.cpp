
#include <SDL3/SDL.h>

#include "shader.hpp"
#include "gamestate.hpp"
#include <algorithm>

struct EnvironmentUniforms {
  float screen_width;
  float screen_height;
  float time;
  float padding; // Pad to maintain a 16-byte boundary (4 floats * 4 bytes = 16)
};


GameState::GameState(SDL_Renderer* renderer){
  // Load the shader code into a buffer of bytes
  mGPUShader = LoadShader(renderer,"./pipelines/my_frag_shader.frag.spv");
  SDL_GPURenderStateCreateInfo state_info;
  SDL_zero(state_info); // zero out the 'state_info'
  state_info.fragment_shader = mGPUShader;
  mCustomRenderState = SDL_CreateGPURenderState(renderer, &state_info);

  // A test surface for us to play with
  Sprite* sky       = new Sprite(0);
  Sprite* buildings1 = new Sprite(1);
  Sprite* buildings2 = new Sprite(2);
  Sprite* character = new Sprite(500);

	sky->LoadTexture(renderer,"./assets/city/Sky.png",0,0,640,480);
	buildings1->LoadTexture(renderer,"./assets/city/Buildings1.png",0,0,640,480);
	buildings2->LoadTexture(renderer,"./assets/city/Buildings2.png",0,0,640,480);
	character->LoadTexture(renderer,"./assets/character.bmp",300,330,32,32);

  mSprites.emplace_back(buildings1);
  mSprites.emplace_back(buildings2);
  mSprites.emplace_back(sky);
  mSprites.emplace_back(character); 
}

GameState::~GameState(){
  SDL_DestroyGPURenderState(mCustomRenderState);
  //    SDL_ReleaseGPUShader(device, shader); // TODO
}

void GameState::Render(SDL_Renderer* renderer){
  SDL_SetRenderDrawColor(renderer, 0x00, 0x66, 0xDD, 0xFF);
  SDL_RenderClear(renderer);

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

  // Sort based on 'order' (e.g. equivalent to a 'z-index')
  std::ranges::sort(mSprites, [](Sprite* a, Sprite* b) { return a->mOrder < b->mOrder;});

  for(int i=0; i < mSprites.size(); i++){
      // Pass in our custom renderer
      SDL_SetGPURenderState(renderer, mCustomRenderState);

      mSprites[i]->Render(renderer);
      /// Back to the default renderer
      SDL_SetGPURenderState(renderer, nullptr);
      // For debugging purposes render a rectangle where we think our shape should be.
      SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
      SDL_RenderRect(renderer, &mSprites[i]->mPosition);
  }

  // ... more drawing operations
  SDL_RenderPresent(renderer);
}

