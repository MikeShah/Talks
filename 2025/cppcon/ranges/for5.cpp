// @file: for5.cpp
// Build and run
// g++-14 -std=c++23 for5.cpp -o prog && ./prog
#include <iostream>
#include <array>
#include <print>

int main(int argc, char* argv[]){

  std::array message {"Hello everyone, welcome!"};
  // find first element and point to it.
  auto data = &message.data()[0]; // or equally 'message.data()';
  auto ptr   = data;
  auto end   = data + message.size(); // last element
  for(/* empty */ ; ptr != end ; ++ptr){
    std::print("{}",*ptr);        // or std::cout << *ptr
  }
  std::println();






  return 0;
}
