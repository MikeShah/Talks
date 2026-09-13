#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>
#include "shader.hpp"

// Load Shader
SDL_GPUShader* LoadShader(SDL_Renderer* renderer, const char* filename){
  static SDL_GPUDevice* gpu_device = SDL_GetGPURendererDevice(renderer);
  // Load your pre-compiled fragment shader bytes (SPIR-V, DXIL, or MSL depending on platform)
  size_t shader_size = 0;
  void* shader_code = SDL_LoadFile(filename, &shader_size); 

  SDL_GPUShaderCreateInfo shader_info;
  SDL_zero(shader_info);
  shader_info = {
    .code_size = shader_size,
    .code = (const Uint8*)shader_code,
    .entrypoint = "main",
    .format = SDL_GPU_SHADERFORMAT_SPIRV, // Match your platform/format
    .stage = SDL_GPU_SHADERSTAGE_FRAGMENT,
    .num_samplers=1,
    .num_uniform_buffers = 1, // One slot for our struct
  };
  shader_info.num_samplers=1;
  SDL_GPUShader* custom_fragment_shader = SDL_CreateGPUShader(gpu_device, &shader_info);
  SDL_free(shader_code); // Free the host allocation after uploading

  return custom_fragment_shader;
}
