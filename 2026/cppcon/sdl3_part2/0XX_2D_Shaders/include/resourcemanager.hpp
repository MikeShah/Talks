#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <SDL3/SDL.h>

#include <unordered_map>
#include <iostream>
#include <string>
#include "shader.hpp"

struct ResourceManager{

  // Constructor
  ResourceManager(){};

  // name - name of the pipeline
  // filepath - where the fragment shader code lives
  void AddPipeline(SDL_Renderer* renderer, std::string name, std::string filepath ){
    // Load the shader code into a buffer of bytes
    if(!mRenderStatePipelines.contains(name)){
      SDL_GPUShader* gpuShader = LoadShader(renderer,filepath.c_str());
      SDL_GPURenderStateCreateInfo state_info;
      SDL_zero(state_info); // zero out the 'state_info'
      state_info.fragment_shader = gpuShader;
      SDL_GPURenderState* renderState = SDL_CreateGPURenderState(renderer, &state_info);
      mRenderStatePipelines[name] = renderState;
    }else{
      std::cout << "Resource Manager already contains " << name << std::endl;
    }
  }

  SDL_GPURenderState* GetPipeline(std::string name){
    if(mRenderStatePipelines.contains(name)){
      return mRenderStatePipelines[name];
    }else{
      return nullptr;
    }
  }

  using StringPipelineMap = std::unordered_map<std::string, SDL_GPURenderState*>;
  StringPipelineMap mRenderStatePipelines;
};

#endif
