// @file: 02.cpp
// 
// linux: 			
// g++ 02.cpp -o prog -lSDL3 && ./prog
// cross-platform: 	
// g++ 02.cpp -o prog `pkg-config --cflags --libs sdl3` && ./prog
#include <SDL3/SDL.h>

int main(int argc, char *argv[]){
	// Initialization
	SDL_Init(SDL_INIT_VIDEO);

	// Setup one SDL window
	SDL_Window* window;
	SDL_Event event;
	window = SDL_CreateWindow("Hello C++ North", 320, 240, 
							  SDL_WINDOW_RESIZABLE);

	// Main application loop
	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_EVENT_QUIT) {
			break;
		}
		if(event.type == SDL_EVENT_KEY_DOWN){
			SDL_Log("Key was pressed!");
			// Retrieve the 'virtual scancode'
			SDL_Log("Keycode: %i",event.key.key);
		}
	}

	// Destroy any SDL objects we have allocated
	SDL_DestroyWindow(window);

	// Quit SDL and shutdown systems we have initialized
	SDL_Quit();

	return 0;
}
