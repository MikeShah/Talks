// @file ./01_current_renderer/main.cpp
// g++ main.cpp -o prog `pkg-config --cflags --libs sdl3` && ./prog
#include <SDL3/SDL.h>

// Helper function to list available render drivers, and
// print the selected renderer for the given window.
void PrintWindowRendererInformation(SDL_Window* window){
	SDL_Log("Available renderer drivers:");
	for (int i = 0; i < SDL_GetNumRenderDrivers(); i++) {
		SDL_Log("%d. %s", i + 1, SDL_GetRenderDriver(i));
	}

	SDL_Renderer* renderer = SDL_GetRenderer(window);

	SDL_PropertiesID props = SDL_GetRendererProperties(renderer);
	const char* current_renderer  = (const char*)SDL_GetStringProperty(props, SDL_PROP_RENDERER_NAME_STRING, "could not find renderer");

	SDL_Log("current renderer is: %s\n",current_renderer);
}

// Program entry point
int main(){
	if(!SDL_Init(SDL_INIT_VIDEO)){
		SDL_Log("Failed!");
		return -1;
	}

	SDL_Window* window;
	window = SDL_CreateWindow("Mike - SDL3", 320, 240, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
	
	PrintWindowRendererInformation(window);



	SDL_Delay(5000);

	SDL_Quit();

	return 0;
}
