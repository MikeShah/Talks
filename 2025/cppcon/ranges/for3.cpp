// @file: for3.cpp
// Build and run
// g++-14 -std=c++23 for3.cpp -o prog && ./prog
#include <iostream>
#include <string>
#include <print>

int main(int argc, char* argv[]){

  char message[] = "Hello everyone, welcome!";




  for(std::size_t i=0; i <        sizeof(message); ++i){
    std::print("{}",message[i]); 
  }
  std::println();






  return 0;
}
