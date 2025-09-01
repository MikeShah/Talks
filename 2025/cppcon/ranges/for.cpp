// @file: for.cpp
// Build and run
// g++-14 -std=c++23 for.cpp -o prog && ./prog
#include <iostream>
#include <string>
#include <print>

int main(int argc, char* argv[]){

  std::string        message = "Hello everyone, welcome!";





  for(std::size_t i=0; i <        message.length(); ++i){
    std::print("{}",message[i]); 
  }
  std::println();






  return 0;
}
