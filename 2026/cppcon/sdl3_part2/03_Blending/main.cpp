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


// Helper function to list available render drivers, and
// print the selected renderer for the given window.
void PrintWindowRendererInformation(SDL_Window* window){
  SDL_Log("Available renderer drivers:");
  for (int i = 0; i < SDL_GetNumRenderDrivers(); i++) {
    SDL_Log("%d. %s", i + 1, SDL_GetRenderDriver(i));
  }

  SDL_Renderer* renderer = SDL_GetRenderer(window);

  SDL_PropertiesID props = SDL_GetRendererProperties(renderer);
  const char* current_renderer  = (const char*)SDL_GetStringProperty(props, SDL_PROP_RENDERER_NAME_STRING, "could not find renderer");

  SDL_Log("current renderer is: %s\n",current_renderer);
}

int main(int argc, char* argv[]){
  // Initialize the video subsystem.
  // iF it returns less than 1, then an
  // error code will be received.
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0){
    std::cout << "SDL could not be initialized: " <<
      SDL_GetError();
  }else{
    std::cout << "SDL video & event system is ready to go!\n";
  }

  // Create a window data type
  // This pointer will point to the 
  // window that is allocated from SDL_CreateWindow
  SDL_Window* window=nullptr;
  // Request a window to be created for our platform
  // The parameters are for the title, x and y position,
  // and the width and height of the window.
  window = SDL_CreateWindow("Mike SDL3 Tutorial - Blending (Press 1-5)", 640,480, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window,"opengles2");
  PrintWindowRendererInformation(window);

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
  // Create the texture
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
  // Hold some state for the purpose of blending in this example
  int  blendMode = 0;   
  // Main application loop
  while(gameIsRunning){
    // (3) Clear and Draw the Screen
    // Gives us a clear "canvas"
    SDL_SetRenderDrawColor(renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    // Do our drawing
    SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);

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

    }
    const bool* keystate = SDL_GetKeyboardState(nullptr);
    if(keystate[SDL_SCANCODE_1]){ blendMode = 1; SDL_Log("1 - BLEND");                }
    if(keystate[SDL_SCANCODE_2]){ blendMode = 2; SDL_Log("2 - BLEND_PREMULTIPLIED");  }
    if(keystate[SDL_SCANCODE_3]){ blendMode = 3; SDL_Log("3 - ADD");                  }
    if(keystate[SDL_SCANCODE_4]){ blendMode = 4; SDL_Log("4 - MOD");                  }
    if(keystate[SDL_SCANCODE_5]){ blendMode = 5; SDL_Log("5 - MUL");                  }

    // Render the first texture normally
    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_NONE);
    SDL_RenderTexture(renderer,texture,NULL,&rectangle);

    // Render the second texture with blending
    switch(blendMode){
      case 1: SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); break;
      case 2: SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND_PREMULTIPLIED); break;
      case 3: SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_ADD); break;
      case 4: SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_MOD); break;
      case 5: SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_MUL); break;
      default: SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_NONE);
    }
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
