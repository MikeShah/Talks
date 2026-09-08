// g++ main.cpp -o prog `pkg-config --cflags --libs sdl3` && ./prog
// Note: You will need 'glslc' or some other compiler to build a spirv shader
//       sudo apt install glslc
//       Then build your shader with:
//       glslc -c my_frag_shader.frag -o my_frag_shader.frag.spv
#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>
#include <string>
#include <vector>
#include <cassert>

struct EnvironmentUniforms {
    float screen_width;
    float screen_height;
    float time;
    float padding; // Pad to maintain a 16-byte boundary (4 floats * 4 bytes = 16)
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

struct SDLApplication{
  SDL_Window*         mWindow;
  SDL_Renderer*       mRenderer;
  SDL_GPURenderState* mCustomRenderState  = nullptr;
  SDL_GPUShader*      mGPUShader    = nullptr;
  SDL_Texture*        mTexture;

  // For my application to run indefinitely
  bool mRunning=true;
  bool mFullScreen=true;

  // Constructor
  SDLApplication(const char* title){
    SDL_Init(SDL_INIT_VIDEO);
    mWindow = SDL_CreateWindow(title, 320, 240,SDL_WINDOW_RESIZABLE);
    mRenderer = SDL_CreateGPURenderer(nullptr, mWindow);
    if(mRenderer==  nullptr){
      assert(0 && "Not able to create HW accelerated renderer");
    }

    SDL_Log("Renderer: %s",SDL_GetRendererName(mRenderer));
    SDL_Log("Available renderer drivers:");
    for (int i = 0; i < SDL_GetNumRenderDrivers(); i++) {
      SDL_Log("%d. %s", i + 1, SDL_GetRenderDriver(i));
    }
    SDL_SetRenderLogicalPresentation(mRenderer, 320, 240,SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // Load the shader code into a buffer of bytes
    mGPUShader = LoadShader(mRenderer,"./my_frag_shader.frag.spv");
    SDL_GPURenderStateCreateInfo state_info;
    SDL_zero(state_info); // zero out the 'state_info'
    state_info.fragment_shader = mGPUShader;
    mCustomRenderState = SDL_CreateGPURenderState(mRenderer, &state_info);

    // A test surface for us to play with
    SDL_Surface* surface = SDL_LoadBMP("./character.bmp");
    mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
//    SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);

    SDL_DestroySurface(surface);
  }
  // Destructor
  ~SDLApplication(){
    SDL_DestroyGPURenderState(mCustomRenderState);
//    SDL_ReleaseGPUShader(device, shader); // TODO
    SDL_DestroyTexture(mTexture);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
  }

  // Advances our loop one iteration
  // It's very easy to add a breakpoint
  void Tick(){
    Input();
    Update();
    Render();
  }

  // Handle input events from I/O or networking devices
  void Input(){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
      // Quit event
      if(event.type == SDL_EVENT_QUIT){
        mRunning=false;
      }
      else if(event.type == SDL_EVENT_KEY_DOWN){
        SDL_Log("a key was pressed: %d",event.key.key);
        if(event.key.key == SDLK_F11){
          mFullScreen = !mFullScreen;
          SDL_SetWindowFullscreen(mWindow, mFullScreen );
        }
      }
      else if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
          SDL_Log("left button clicked %d",event.button.button);
        }  
        if(event.button.button == SDL_BUTTON_MIDDLE){
          SDL_Log("middle button clicked %d",event.button.button);
        }  
        if(event.button.button == SDL_BUTTON_RIGHT){
          SDL_Log("right button clicked %d",event.button.button);
        }  
        SDL_Log("Clicks: %d",event.button.clicks);
      }
    }

    float x,y;
    // Get the 'local' within current mWindow mouse position
    SDL_MouseButtonFlags mouse = SDL_GetMouseState(&x, &y);
    // Get mouse position outside mWindow, across multiple monitors.
    //SDL_MouseButtonFlags mouse = SDL_GetGlobalMouseState(&x, &y);
    // SDL_Log("x,y: %f,%f",x,y);

    // Application/Game logic
    // ...
  }

  void Update(){
  }

  void Render(){
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(mRenderer);
    // Draw a texture
    static SDL_FRect dst_rect{.x = 50, .y = 25, .w = 24, .h = 28 };
    dst_rect.x += 0.1f;

    // STAGE 2: Populate and Modify Data structures
    EnvironmentUniforms env_data = {
        .screen_width = 320.0f,
        .screen_height = 240.0f,
        .time = (float)SDL_GetTicks() / 1000.0f
    };
    // STAGE 3: Inject parameters using SDL_SetGPURenderStateFragmentUniforms
    // Pass Environment data to binding uniform Slot 0
    if (!SDL_SetGPURenderStateFragmentUniforms(mCustomRenderState, 0, &env_data, sizeof(env_data))) {
        SDL_Log("Failed to push data to Fragment Uniform Slot 0: %s", SDL_GetError());
    }

    // Pass in our custom renderer
    SDL_SetGPURenderState(mRenderer, mCustomRenderState);
    SDL_RenderTexture(mRenderer, mTexture, nullptr, &dst_rect);
    /// Back to the default renderer
    SDL_SetGPURenderState(mRenderer, nullptr);
    // For debugging purposes render a rectangle where we think our shape should be.
    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderRect(mRenderer, &dst_rect);


    // ... more drawing operations
    SDL_RenderPresent(mRenderer);
  }

  // Main application loop
  void MainLoop(){
    Uint64 fps=0; // Number of frames per second
    Uint64 lastTime = 0;

    // Our infinite loop
    while(mRunning){
      Uint64 currentTick = SDL_GetTicks();
      Tick();
      SDL_Delay(16);
      fps++;
      // Per frame calculation of elapsed time
      Uint64 deltaTime = SDL_GetTicks() - currentTick;

      // FPS Calculation
      if(currentTick > lastTime + 1000){
        lastTime = currentTick; 
        std::string title;
        title += "Mike's SDL3 Tutorials - FPS " + std::to_string(fps);
        SDL_SetWindowTitle(mWindow,title.c_str());
        fps=0;
      }
    }
  }
};

// Entry Point
int main(int argc, char* argv[]){
  SDLApplication app("Mike's SDL3 Tutorials");
  app.MainLoop();
  return 0;
}


