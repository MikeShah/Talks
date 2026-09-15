// On linux compile with:
// g++ -std=c++26 main.cpp -o prog -lSDL3
// On windows compile with (if using mingw)
// g++ main.cpp -o prog.exe -lmingw32 -lSDL3main -lSDL3
// On Mac compile with:
// clang++ main.cpp -I/Library/Frameworks/SDL3.framework/Headers -F/Library/Frameworks -framework SDL3

// C++ Standard Libraries
#include <iostream>
// Third Party
#include <SDL3/SDL.h> // For Mac, use <SDL.h>

int main(int argc, char* argv[]){
  // Create a window data type
  // This pointer will point to the 
  // window that is allocated from SDL_CreateWindow
  SDL_Window* window=nullptr;

  // Initialize the video subsystem.
  // iF it returns less than 1, then an
  // error code will be received.
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0){
    std::cout << "SDL could not be initialized: " <<
      SDL_GetError();
  }else{
    std::cout << "SDL video system is ready to go\n";
  }
  // Request a window to be created for our platform
  // The parameters are for the title, x and y position,
  // and the width and height of the window.
  window = SDL_CreateWindow("C++ SDL3 Window", 640,480, 0);

  SDL_Renderer* renderer = nullptr;
  renderer = SDL_CreateRenderer(window,nullptr);

  SDL_Surface* surface = SDL_LoadBMP("./images/kong.bmp");
  // Set the color key after loading the surface, and before the texture is generated
  // Get the format details
  const SDL_PixelFormatDetails* details = SDL_GetPixelFormatDetails(surface->format);
  // Get the color palette
  SDL_Palette* palette = SDL_GetSurfacePalette(surface);
  // Set the color key
  Uint32 colorKey = SDL_MapRGB(details, palette, 0xFF, 0x00, 0xFF);
  // Set the surface
  SDL_SetSurfaceColorKey(surface, true, colorKey);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);

  SDL_DestroySurface(surface); 

  // Create a rectangle
  SDL_FRect rectangle;
  rectangle.x = 50;
  rectangle.y = 100;
  rectangle.w = 200;
  rectangle.h = 200;

  SDL_FRect rectangle2;
  rectangle2.x = 50;
  rectangle2.y = 100;
  rectangle2.w = 200;
  rectangle2.h = 200;


  // Infinite loop for our application
  bool gameIsRunning = true;
  // Main application loop
  while(gameIsRunning){
    SDL_Event event;

    // (1) Handle Input
    // Start our event loop
    while(SDL_PollEvent(&event)){
      // Handle each specific event
      if(event.type == SDL_EVENT_QUIT){
        gameIsRunning= false;
      }
      if(event.type == SDL_EVENT_MOUSE_MOTION){
        rectangle2.x = event.motion.x;
        rectangle2.y = event.motion.y;
      }
      if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
          SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_ADD);
        }
        else if(event.button.button == SDL_BUTTON_MIDDLE){
          SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
        }
        else if(event.button.button == SDL_BUTTON_RIGHT){
          SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_MOD);
        }
      }
      else{
        SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
      }
    }
    // (2) Handle Updates

    // (3) Clear and Draw the Screen
    // Gives us a clear "canvas"
    SDL_SetRenderDrawColor(renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Do our drawing
    SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawLine(renderer,5,5,200,220);

    //        SDL_RenderDrawRect(renderer,&rectangle);
    SDL_RenderTexture(renderer,texture,NULL,&rectangle);
    SDL_RenderTexture(renderer,texture,NULL,&rectangle2);


    // Finally show what we've drawn
    SDL_RenderPresent(renderer);

  }

  SDL_DestroyTexture(texture);
  // We destroy our window. We are passing in the pointer
  // that points to the memory allocated by the 
  // 'SDL_CreateWindow' function. Remember, this is
  // a 'C-style' API, we don't have destructors.
  SDL_DestroyWindow(window);

  // our program.
  SDL_Quit();
  return 0;
}
