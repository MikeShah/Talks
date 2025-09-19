// @file: 07_animated.cpp.cpp
// 
// linux: 			
// g++ 07_animated.cpp.cpp -o prog -lSDL3 && ./prog
// cross-platform: 	
// g++ 07_animated.cpp.cpp -o prog `pkg-config --cflags --libs sdl3` && ./prog
#include <SDL3/SDL.h>

struct SDLApplication{
	SDL_Window *mWindow;
	SDL_Renderer *mRenderer;
	SDL_Surface* mSurface;
	SDL_Texture* mTexture;

	SDLApplication(){
		// Initialization
		SDL_CreateWindowAndRenderer("Hello CppCon", 320, 240, 
				SDL_WINDOW_RESIZABLE, &mWindow, &mRenderer);
		SDL_Log("Renderer: %s",SDL_GetRendererName(mRenderer));
	}
	void Initialization(){
		SDL_Init(SDL_INIT_VIDEO);
		
		mSurface = SDL_LoadBMP("mario.bmp");
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
		// Main application loop
		int state=0;
	
		SDL_FRect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = 60;
		rect.h = 80;
		SDL_FRect src_rect;
		src_rect.x = 0;
		src_rect.y = 0;
		src_rect.w = 30;
		src_rect.h = 40;

		while (1) {
			SDL_Event event;
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


			// Render a texture, seleting the texels based on
			// the rectangle.
			SDL_RenderTexture(mRenderer, mTexture, &src_rect, &rect);

			SDL_Delay(100);
			src_rect.x += 32;
			if(src_rect.x > 150){
				src_rect.x=0;
			}

			// Present all 'drawing' operations that have 
			// been queued up to this point.
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
