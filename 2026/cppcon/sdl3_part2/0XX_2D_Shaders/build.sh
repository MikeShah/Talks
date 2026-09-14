# @file: build.sh
# NOTE: This is a somewhat 'lazy' build file, in that we don't need to rebuild the
#       C++ and the shader code every time, but for a small project this is fine.
 
rm prog
# Compile C++ program
g++ -g3 -std=c++26 ./src/*.cpp -I./include -o prog `pkg-config --cflags --libs sdl3` 

# Recompile Shaders into spir-v
# Make sure to install: apt install glslc
glslc -c ./pipelines/my_frag_shader.frag -o ./pipelines/my_frag_shader.frag.spv

# Run
./prog
