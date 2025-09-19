// @file: 03_renderer.cpp
// 
// linux: 			
// g++ 03_renderer.cpp -o prog -lSDL3 && ./prog
// cross-platform: 	
// g++ 03_renderer.cpp -o prog `pkg-config --cflags --libs sdl3` && ./prog
#include <SDL3/SDL.h>

int main(int argc, char *argv[]){
	// structures
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	// Initialization
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Hello CppCon", 320, 240, 
								SDL_WINDOW_RESIZABLE, &window, &renderer);
	SDL_Log("Renderer: %s",SDL_GetRendererName(renderer));

	// Main application loop
	int state=0;
	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_EVENT_QUIT) {
			break;
		}

		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0xFF,0x00,0x0,0xFF);				
		SDL_RenderPresent(renderer);
	}

	// Explicit cleanup of allocated resources
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
