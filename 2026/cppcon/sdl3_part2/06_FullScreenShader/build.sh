# Compile shaders
glslc -c blending.frag -o blending.frag.spv
glslc -c default.frag -o default.frag.spv

# Compile and build our executable
g++ -std=c++26 main.cpp -o prog -lSDL3 && ./prog
