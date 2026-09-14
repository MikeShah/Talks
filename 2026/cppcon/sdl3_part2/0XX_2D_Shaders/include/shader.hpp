#ifndef SHADER_HPP
#define SHADER_HPP

#include <SDL3/SDL.h>

// Load Shader
SDL_GPUShader* LoadShader(SDL_Renderer* renderer, const char* filename);

#endif
