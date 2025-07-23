// @file: 00_commented.cpp
// 
// linux: 			
// g++ 00_commented.cpp -o prog -lSDL3 && ./prog
// cross-platform: 	
// g++ 00_commented.cpp -o prog `pkg-config --cflags --libs sdl3` && ./prog

// Third-party library
#include <SDL3/SDL.h>

int main(int argc, char* argv[]){

    // Initialize SDL with the video subsystem.
    // If it returns less than false then an
    // error code will be received.
    SDL_Init(SDL_INIT_VIDEO);

    // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
	SDL_Window* window;
    // Request a window to be created for our platform
    // The parameters are for the title and the width 
	// and height of the window.
	window = SDL_CreateWindow("Hello C++ North", 320, 240, 
 							  SDL_WINDOW_RESIZABLE);

    // We add a delay in order to see that our window
    // has successfully popped up.
    SDL_Delay(3000);

    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(window);
    
    // We safely uninitialize SDL2, that is, we are
    // taking down the subsystems here before we exit
    // our program.
    SDL_Quit();

    return 0;
}
