// @file: 02_better.cpp
// 
// A few ways to build:
// linux: 					g++ 02_better.cpp -o prog -lSDL3 && ./prog
// cross-platform: 	g++ 02_better.cpp -o prog `pkg-config --cflags --libs sdl3` && ./prog
#include <SDL3/SDL.h>

int main(int argc, char *argv[]){
	// Initialization
	SDL_Init(SDL_INIT_VIDEO);

	// Setup one SDL window
	SDL_Window* window;
	window = SDL_CreateWindow("Hello C++ North", 320, 240,
							   SDL_WINDOW_RESIZABLE);

	// Main application loop
	while (1) {
		SDL_Event event;
		
		// 'handle' queued up events in a while loop.
		// This helps ensure we handle all of our events.
		while(SDL_PollEvent(&event)){
			if (event.type == SDL_EVENT_QUIT) {
				break;
			}
			if(event.type == SDL_EVENT_KEY_DOWN){
				SDL_Log("Key was pressed!");
				// Retrieve the 'virtual scancode'
				SDL_Log("Keycode: %i",event.key.key);
			}
		}
	}
	// Destroy any SDL objects we have allocated
	SDL_DestroyWindow(window);

	// Quit SDL and shutdown systems we have initialized
	SDL_Quit();

	return 0;
}
