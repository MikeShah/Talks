// @file: 02.cpp
// 
// A few ways to build:
// linux: 					g++ 02.cpp -o prog -lSDL3 && ./prog
// cross-platform: 	g++ 02.cpp -o prog `pkg-config --cflags --libs sdl3` && ./prog
#include <SDL3/SDL.h>

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return 3;
	}

	if (!SDL_CreateWindowAndRenderer("Hello C++ North", 320, 240, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
		return 3;
	}else{
		SDL_Log("Renderer: %s",SDL_GetRendererName(renderer));
	}

	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_EVENT_QUIT) {
			break;
		}

		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0x0,0xFF);				
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
