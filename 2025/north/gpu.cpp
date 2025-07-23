// gcc gpu.cpp -o prog `pkg-config --cflags --libs sdl3` && ./prog
#include <SDL3/SDL.h>

// TODO: 
// Look at SDL_ShaderCross
// In CppNorth Video, talk about SpirV (it's purpose, and how it's an IR bytecode, similar to how some of you might think of LLVM bytecode).
//


int main(){

	// (1) Before we call any SDL function
	if(!SDL_Init(SDL_INIT_VIDEO)){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Ooops, no sdl", SDL_GetError());
		return -1; 
	}
	SDL_SetLogPriorities(SDL_LOG_PRIORITY_VERBOSE);
	// TODO:
	// Can do more with: https://wiki.libsdl.org/SDL3/SDL_SetLogOutputFunction

	// (2) thing is to create a window
	SDL_Window* window;
	window = SDL_CreateWindow("SDL3 window with GPU Example API",640,480, 0);

	// (3) Setup the GPU Device API
	SDL_GPUDevice* gpuDevice = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV,
			true,
			nullptr/*"vulkan"*/);

	// Claim a window for creating a 'swapchain' structure.
	// The 'swapchain' is the collection of buffers used to effectively refresh our
	// window with new pixels. If you've heard of 'double buffering' this is the similar
	// idea for how we present frames to our window.
	// https://en.wikipedia.org/wiki/Swap_chain
	if(!SDL_ClaimWindowForGPUDevice(gpuDevice,window)){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Ooops, device and window error", SDL_GetError());
		return -1;
	}

	if(nullptr == window){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Ooops, no window", SDL_GetError());
	}

/*
	GPUShader* vertex;
	GPUShader* fragment;
	SDL_GPUGraphicsPipelineCreateInfo* info = {vertex,fragment,
	pipeline = SDL_CreateGPUGraphicsPipeline(gpuDevice,info);

*/
	bool done=false;
	while(!done){
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			if(SDL_EVENT_QUIT == event.type){
				done = true;
			}
		}

		// render
		//
		// acquire command buffer
		SDL_GPUCommandBuffer* cmdBuffer = SDL_AcquireGPUCommandBuffer(gpuDevice);
		// acquire swapchain texture
		SDL_GPUTexture* swapChainTexture;
		SDL_WaitAndAcquireGPUSwapchainTexture(cmdBuffer,window,&swapChainTexture,nullptr,nullptr);
		// begin render pass
		// Note: This is using C++20 feature for initialization,
		//       This might also be compiler dependent.
		//       **May** need to show other way of doing this.
		// NOTE: Helpful to show in source code
		//       https://github.com/libsdl-org/SDL/blob/main/include/SDL3/SDL_gpu.h
		//       the enumerations for these values.
		SDL_GPUColorTargetInfo colorTargetInfo = {
			.texture = swapChainTexture,
			.clear_color = {0.0,0.5,0.7,1.0},
			.load_op = SDL_GPU_LOADOP_CLEAR,
			.store_op = SDL_GPU_STOREOP_STORE
		};
		SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(cmdBuffer,&colorTargetInfo,1,nullptr);
		// Now need to build out shaders

		// draw stuff
		// end render pass
		// NOTE: Need to show an example of what happens when I 'omit' the renderpass.
		//
		//       I got an interesting 'abort' message here when that happened otherwise.
		SDL_EndGPURenderPass(renderPass);
		// more render passes
		// submit command buffer so GPU can process the commands
		if(!SDL_SubmitGPUCommandBuffer(cmdBuffer)){
			return -1;
		}

	}

	SDL_DestroyGPUDevice(gpuDevice);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
