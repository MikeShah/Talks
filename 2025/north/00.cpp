// @file: 00.cpp
// 
// linux: 			
// g++ 00.cpp -o prog -lSDL3 && ./prog
// cross-platform: 	
// g++ 00.cpp -o prog `pkg-config --cflags --libs sdl3` && ./prog
#include <SDL3/SDL.h>

int main(int argc, char *argv[]){
	// Initialization
	SDL_Init(SDL_INIT_VIDEO);

	// Setup one SDL window
	SDL_Window* window;
	window = SDL_CreateWindow("Hello C++ North", 320, 240, SDL_WINDOW_RESIZABLE);

	// Pause program so we can see window for 3 seconds
	SDL_Delay(3000);

	// Destroy any SDL objects we have allocated
	SDL_DestroyWindow(window);

	// Quit SDL and shutdown systems we have initialized
	SDL_Quit();

	return 0;
}
