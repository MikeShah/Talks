
#include <SDL3/SDL.h>

#include "gamestate.hpp"
#include <algorithm>


GameState::GameState(SDL_Renderer* renderer){
  // TODO:
  // Homework activity to make this 'data-driven'
  // For example -- think about a .json configuration you could
  // have for all of the pipelines and sprites.

  // Create a new resource manager
  mResourceManager = new ResourceManager();
  // Add some render states
  mResourceManager->AddPipeline(renderer,"sine","./pipelines/sine.frag.spv");
  mResourceManager->AddPipeline(renderer,"blend","./pipelines/blend.frag.spv");

  // A test surface for us to play with
  Sprite* sky       = new Sprite(renderer,0,"sine");
  Sprite* buildings1 = new Sprite(renderer,1,"default");
  //Sprite* buildings2 = new Sprite(renderer,2,"default");
  Sprite* character = new Sprite(renderer,500,"blend");

  sky->LoadTexture(renderer,"./assets/city/Sky.png",0,0,640,480);
  buildings1->LoadTexture(renderer,"./assets/city/Buildings1.png",0,0,640,480);
//  buildings2->LoadTexture(renderer,"./assets/city/Buildings2.png",0,0,640,480);
  character->LoadTexture(renderer,"./assets/kong.bmp",300,330,128,128);

  mSprites.emplace_back(buildings1);
 // mSprites.emplace_back(buildings2);
  mSprites.emplace_back(sky);
  mSprites.emplace_back(character); 
}

GameState::~GameState() {}

void GameState::Render(SDL_Renderer* renderer){
  SDL_SetRenderDrawColor(renderer, 0x00, 0x66, 0xDD, 0xFF);
  SDL_RenderClear(renderer);

  // Sort based on 'order' (e.g. equivalent to a 'z-index')
  std::ranges::sort(mSprites, [](Sprite* a, Sprite* b) { return a->mOrder < b->mOrder;});

  float mx,my;
  SDL_GetMouseState(&mx,&my);
  // Update our uniforms each frame
  mGameStateUniforms = {
    .screen_width = 640.0f,
    .screen_height = 480.0f,
    .mouseX = mx,
    .mouseY = my,
    .time = (float)SDL_GetTicks() / 1000.0f,
    .color_scale = 1.0f,
    .alpha = my/ 480.0f,
    .padding = 0.0f
  };

  for(int i=0; i < mSprites.size(); i++){
    // Render each sprite with their specific pipelines and shared uniforms
    SDL_Log("sprite render pipeline: %s",mSprites[i]->mRenderStateName.c_str()); 
    SDL_GPURenderState* renderState = mResourceManager->GetPipeline(mSprites[i]->mRenderStateName);
    for(auto&[key,value] : mResourceManager->mRenderStatePipelines){
      std::cout << "key:" << key << std::endl;
    }

    if(renderState == nullptr){
      // Note: This will fall back on the 'default' SDL build in renderer in the 2D API
      //SDL_Log("Failed to find corrct render pipeline");
    }else{
      // GameState Uniform Data binding uniform Slot 0
      if (!SDL_SetGPURenderStateFragmentUniforms(renderState, 0, &mGameStateUniforms, sizeof(GameStateUniforms))) {
        SDL_Log("Failed to push data to Fragment Uniform Slot 0: %s", SDL_GetError());
      }
    }
    SDL_SetGPURenderState(renderer, renderState);
    mSprites[i]->Render(renderer);
  }

  // Do a second render pass with rectangles
  /// Back to the default renderer for the bounding boxes
  SDL_SetGPURenderState(renderer, nullptr);
  for(int i=0; i < mSprites.size(); i++){
    // For debugging purposes render a rectangle where we think our shape should be.
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderRect(renderer, &mSprites[i]->mPosition);
  }

  // ... more drawing operations
  SDL_RenderPresent(renderer);
}

