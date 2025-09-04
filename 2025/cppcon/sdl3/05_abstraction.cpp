// @file: 05_abstraction.cpp
// 
// linux: 			
// g++ 05_abstraction.cpp -o prog -lSDL3 && ./prog
// cross-platform: 	
// g++ 05_abstraction.cpp -o prog `pkg-config --cflags --libs sdl3` && ./prog
#include <SDL3/SDL.h>

struct SDLApplication{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDLApplication(){
		// Initialization
		SDL_CreateWindowAndRenderer("Hello C++ North", 320, 240, 
				SDL_WINDOW_RESIZABLE, &window, &renderer);
		SDL_Log("Renderer: %s",SDL_GetRendererName(renderer));
	}
	void Initialization(){
		SDL_Init(SDL_INIT_VIDEO);
	}

	void Cleanup(){
		// Explicit cleanup of allocated resources
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void MainLoop(){
		SDL_Event event;
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
	}
};

int main(int argc, char *argv[]){
	SDLApplication app;
	app.Initialization();
	app.MainLoop();
	app.Cleanup();

	return 0;
}
