// g++ ./src/*.cpp -I./include -o prog `pkg-config --cflags --libs sdl3` && ./prog
// Note: You will need 'glslc' or some other compiler to build a spirv shader
//       sudo apt install glslc
//       Then build your shader with:
//       glslc -c my_frag_shader.frag -o my_frag_shader.frag.spv
#include "gameapplication.hpp"

// Entry Point
int main(int argc, char* argv[]){

	// https://wiki.libsdl.org/SDL3/SDL_GetVersion
	const int compiled = SDL_VERSION;  /* hardcoded number from SDL headers */
	const int linked = SDL_GetVersion();  /* reported by linked SDL library */
	SDL_Log("We compiled against SDL version %d.%d.%d ...\n", SDL_VERSIONNUM_MAJOR(compiled), SDL_VERSIONNUM_MINOR(compiled), SDL_VERSIONNUM_MICRO(compiled));
	SDL_Log("We are linking against SDL version %d.%d.%d.\n", SDL_VERSIONNUM_MAJOR(linked), SDL_VERSIONNUM_MINOR(linked), SDL_VERSIONNUM_MICRO(linked));

  
  // Simple and somewhat testable way to struture a game.
  GameApplication app("Mike's SDL3 Tutorials", argc, argv);
  app.MainLoop();


  return 0;
}


/*
// Reflection()
void Reflect(){
// Reflect on the Greet struct type
constexpr auto type_refl = ^^GameState;

// Print the name of the reflected type
std::cout << "Type name: " << std::meta::name_of(type_refl) << '\n';

// Iterate and inspect non-static data members
template for (constexpr auto member : std::meta::non_static_data_members_of(^^Greet)) {
std::cout << "Member name: " << std::meta::name_of(member) << '\n';
}
}
*/
