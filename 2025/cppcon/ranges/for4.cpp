// @file: for4.cpp
// Build and run
// g++-14 -std=c++23 for4.cpp -o prog && ./prog
#include <iostream>
#include <array>
#include <print>

int main(int argc, char* argv[]){

  std::array message {"Hello everyone, welcome!"};
  // Class Template Argument Deduction (CTAD),
  // allows us to omit type and size parameters
  // for std::array if it can be inferred.

  for(std::size_t i=0; i < message.size(); ++i){
    std::print("{}",message[i]); 
  }
  std::println();






  return 0;
}
