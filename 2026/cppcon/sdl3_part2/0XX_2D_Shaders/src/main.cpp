// @file: main.cpp
// g++ ./src/*.cpp -I./include -o prog `pkg-config --cflags --libs sdl3` && ./prog
// Note: You will need 'glslc' or some other compiler to build a spirv shader
//       sudo apt install glslc
//       Then build your shader with:
//       glslc -c my_frag_shader.frag -o my_frag_shader.frag.spv
#include "gameapplication.hpp"
#include "util.hpp"

// Run is a separate function such that we can 
// put a breakpoint on it, and it is useful later on
// if we want to 'launch' a game and implement 'run' 
// as a function in a .dll.
void run(int argc, char* argv[]){
  // Simple and somewhat testable way to struture a game.
  GameApplication app("Mike's SDL3 Tutorials", argc, argv);
  app.MainLoop();
}

// Entry Point
int main(int argc, char* argv[]){

  // Some debug information about the version of SDL linked
  PrintSDLVersionInformation();

  // Forward Arguments
  // Note: For folks that love exceptions, you can wrap 'run'
  //       in a try/catch block for debugging.
  run(argc,argv);

  return 0;
}


