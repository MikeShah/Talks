// g++ ./src/*.cpp -I./include -o prog `pkg-config --cflags --libs sdl3` && ./prog
// Note: You will need 'glslc' or some other compiler to build a spirv shader
//       sudo apt install glslc
//       Then build your shader with:
//       glslc -c my_frag_shader.frag -o my_frag_shader.frag.spv
#include "gameapplication.hpp"

// Entry Point
int main(int argc, char* argv[]){
  GameApplication app("Mike's SDL3 Tutorials");
  app.MainLoop();
  return 0;
}
