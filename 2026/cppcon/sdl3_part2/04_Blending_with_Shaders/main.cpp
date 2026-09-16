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

struct BlendingUniforms {
  float alpha;
};

// Data to pass into 'default' fragment shader
struct Constants{
      float color_scale;
};

// Load Shader
SDL_GPUShader* LoadShader(SDL_Renderer* renderer, const char* filename){
  static SDL_GPUDevice* gpu_device = SDL_GetGPURendererDevice(renderer);
  // Load your pre-compiled fragment shader bytes (SPIR-V, DXIL, or MSL depending on platform)
  size_t shader_size = 0;
  void* shader_code = SDL_LoadFile(filename, &shader_size); 

  SDL_GPUShaderCreateInfo shader_info;
  SDL_zero(shader_info);
  shader_info = {
    .code_size = shader_size,
    .code = (const Uint8*)shader_code,
    .entrypoint = "main",
    .format = SDL_GPU_SHADERFORMAT_SPIRV, // Match your platform/format
    .stage = SDL_GPU_SHADERSTAGE_FRAGMENT,
    .num_samplers=1,
    .num_uniform_buffers = 1, // One slot for our struct
  };
  shader_info.num_samplers=1;
  SDL_GPUShader* custom_fragment_shader = SDL_CreateGPUShader(gpu_device, &shader_info);
  SDL_free(shader_code); // Free the host allocation after uploading

  return custom_fragment_shader;
}

SDL_GPURenderState* CreateRenderState(SDL_Renderer* renderer, const char* filename){
  SDL_GPUShader* gpuShader = LoadShader(renderer,filename);
  SDL_GPURenderStateCreateInfo state_info;
  SDL_zero(state_info); // zero out the 'state_info'
  state_info.fragment_shader = gpuShader;
  return SDL_CreateGPURenderState(renderer, &state_info);
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
  window = SDL_CreateWindow("Mike SDL3 Tutorial - Blending/opacity (Press 1-4)", 640,480, 0);
  //SDL_Renderer* renderer = SDL_CreateRenderer(window,"vulkan");
  SDL_Renderer* renderer = SDL_CreateGPURenderer(nullptr, window);

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

  SDL_GPURenderState* renderState   = CreateRenderState(renderer, "./blending.frag.spv");
  SDL_GPURenderState* defaultState  = CreateRenderState(renderer, "./default.frag.spv");

  // Infinite loop for our application
  bool gameIsRunning = true;
  // Hold some state for the purpose of blending in this example
  float blendMode = 0.25;   
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
    if(keystate[SDL_SCANCODE_1]){ blendMode = 0.25; SDL_Log("0.25");                }
    if(keystate[SDL_SCANCODE_2]){ blendMode = 0.5; SDL_Log("0.50");  }
    if(keystate[SDL_SCANCODE_3]){ blendMode = 0.75; SDL_Log("0.75");                  }
    if(keystate[SDL_SCANCODE_4]){ blendMode = 1.0; SDL_Log("1.0");                  }


    static float scale = 1.0f;
    static bool   grow = true;
    Constants constants_data  = {
      .color_scale = scale,
    };

    if(grow){    
      scale+= 0.001;
    }else{
      scale-= 0.001;
    }
    if (scale > 2.0f){
      grow = false;
    }
    if(scale < 0.001){
      grow = true;
    }
    // Pass data to binding uniform Slot 0
    if (!SDL_SetGPURenderStateFragmentUniforms(defaultState, 0, &constants_data, sizeof(constants_data))) {
      SDL_Log("Failed to push data to Fragment Uniform Slot ?: %s", SDL_GetError());
    }
    /// Back to the default renderer that we 'copied' but sending in our custom data
    SDL_SetGPURenderState(renderer, defaultState);
//    SDL_SetGPURenderState(renderer, nullptr);
    SDL_RenderTexture(renderer,texture,NULL,&rectangle);

    // Pass in our custom renderer
    // Pass data to binding uniform Slot 0
    BlendingUniforms blending_data  = {
      .alpha = blendMode,
    };
    if (!SDL_SetGPURenderStateFragmentUniforms(renderState, 0, &blending_data, sizeof(blending_data))) {
      SDL_Log("Failed to push data to Fragment Uniform Slot ?: %s", SDL_GetError());
    }
    SDL_SetGPURenderState(renderer, renderState);
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
