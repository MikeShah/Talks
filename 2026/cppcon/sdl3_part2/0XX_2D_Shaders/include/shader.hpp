#ifndef SHADER_HPP
#define SHADER_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>

// Load Shader
SDL_GPUShader* LoadShader(SDL_Renderer* renderer, const char* filename);

#endif
