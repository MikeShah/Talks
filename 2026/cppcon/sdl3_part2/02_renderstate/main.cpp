// @file ./02_current_renderer/main.cpp
// g++ main.cpp -o prog `pkg-config --cflags --libs sdl3` && ./prog
#include <SDL3/SDL.h>


// Program entry point
int main(){
	if(!SDL_Init(SDL_INIT_VIDEO)){
		SDL_Log("Failed!");
		return -1;
	}

	SDL_Window* window;
	window = SDL_CreateWindow("Mike - SDL3", 320, 240, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
	
	// Clear any custom render state and use the default
	SDL_SetGPURenderState(renderer, nullptr);

typedef struct SDL_GPURenderStateCreateInfo
{
    SDL_GPUShader *fragment_shader; /**< The fragment shader to use when this render state is active */

    Sint32 num_sampler_bindings;    /**< The number of additional fragment samplers to bind when this render state is active */
    const SDL_GPUTextureSamplerBinding *sampler_bindings;   /**< Additional fragment samplers to bind when this render state is active */

    Sint32 num_storage_textures;    /**< The number of storage textures to bind when this render state is active */
    SDL_GPUTexture *const *storage_textures;    /**< Storage textures to bind when this render state is active */

    Sint32 num_storage_buffers;     /**< The number of storage buffers to bind when this render state is active */
    SDL_GPUBuffer *const *storage_buffers;      /**< Storage buffers to bind when this render state is active */

    SDL_PropertiesID props;         /**< A properties ID for extensions. Should be 0 if no extensions are needed. */
} SDL_GPURenderStateCreateInfo;


	SDL_Delay(5000);

	SDL_Quit();

	return 0;
}
