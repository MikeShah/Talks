// @file: 03.cpp
// 
// linux: 			
// g++ 03.cpp -o prog -lSDL3 && ./prog
// cross-platform: 	
// g++ 03.cpp -o prog `pkg-config --cflags --libs sdl3` && ./prog
#include <SDL3/SDL.h>
int main(int argc, char *argv[]){
	// structures
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	// Initialization
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Hello C++ North", 320, 240, 
								SDL_WINDOW_RESIZABLE, &window, &renderer);
	SDL_Log("Renderer: %s",SDL_GetRendererName(renderer));
	// Main application loop
	int state=0;
	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_EVENT_QUIT) {
			break;
		}
		if(event.type == SDL_EVENT_KEY_DOWN && event.key.key==SDLK_R){
			state =1;
		}else if(event.type == SDL_EVENT_KEY_DOWN){
			state =0;
		}

		SDL_RenderClear(renderer);

		if(state){
			SDL_SetRenderDrawColor(renderer, 0xFF,0x00,0x0,0xFF);				
		}else{
			SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0x0,0xFF);				
		}

		SDL_RenderPresent(renderer);
	}
	// Explicit cleanup of allocated resources
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
