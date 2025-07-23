// @file: 06_texture.cpp
// 
// linux: 			
// g++ 06_texture.cpp -o prog -lSDL3 && ./prog
// cross-platform: 	
// g++ 06_texture.cpp -o prog `pkg-config --cflags --libs sdl3` && ./prog
#include <SDL3/SDL.h>

struct SDLApplication{
	SDL_Window *mWindow;
	SDL_Renderer *mRenderer;
	SDL_Surface* mSurface;
	SDL_Texture* mTexture;

	SDLApplication(){
		// Initialization
		SDL_CreateWindowAndRenderer("Hello C++ North", 320, 240, 
				SDL_WINDOW_RESIZABLE, &mWindow, &mRenderer);
		SDL_Log("Renderer: %s",SDL_GetRendererName(mRenderer));
	}
	void Initialization(){
		SDL_Init(SDL_INIT_VIDEO);
		
		mSurface = SDL_LoadBMP("test.bmp");
		mTexture = SDL_CreateTextureFromSurface(mRenderer,mSurface);
	}

	void Cleanup(){
		// Explicit cleanup of allocated resources
		SDL_DestroyTexture(mTexture);
		SDL_DestroyRenderer(mRenderer);
		SDL_DestroyWindow(mWindow);
		SDL_Quit();
	}

	void MainLoop(){
		SDL_Event event;
		// Main application loop
		int state=0;
	
		SDL_FRect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = 64;
		rect.h = 64;

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

			SDL_RenderClear(mRenderer);

			if(state){
				SDL_SetRenderDrawColor(mRenderer, 0xFF,0x00,0x0,0xFF);				
			}else{
				SDL_SetRenderDrawColor(mRenderer, 0xFF,0xFF,0x0,0xFF);	
			}

			// Render a texture
			SDL_RenderTexture(mRenderer, mTexture, nullptr, &rect);

			// Present all 'drawing' operations that have been queued up to this point.
			SDL_RenderPresent(mRenderer);
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
