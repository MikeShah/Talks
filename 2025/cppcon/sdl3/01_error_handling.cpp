// @file: 01_error_handling.cpp
// 
// A few ways to build:
// linux: 					g++ 01_error_handling.cpp -o prog -lSDL3 && ./prog
// cross-platform: 	g++ 01_error_handling.cpp -o prog `pkg-config --cflags --libs sdl3` && ./prog
#include <SDL3/SDL.h>

int main(int argc, char *argv[]){
	// Initialization
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
					 "Couldn't initialize SDL: %s", 
					 SDL_GetError());
		return 3;
	}

	// Setup one SDL window
	SDL_Window* window;
	window = SDL_CreateWindow("Hello CppCon", 320, 240, SDL_WINDOW_RESIZABLE);

	if (nullptr == window) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
					 "Couldn't create window and renderer: %s", 
					 SDL_GetError());
		return 3;
	}

	// Pause program so we can see window for 3 seconds
	SDL_Delay(3000);

	// Destroy any SDL objects we have allocated
	SDL_DestroyWindow(window);

	// Quit SDL and shutdown systems we have initialized
	SDL_Quit();

	return 0;
}

