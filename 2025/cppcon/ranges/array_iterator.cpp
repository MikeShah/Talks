// @file: array_iterator.cpp
// Build and run
// g++-14 -std=c++23 array_iterator.cpp -o prog && ./prog
#include <iostream>
#include <array>
#include <print>

int main(int argc, char* argv[]){

  std::array message {'H','e','l','l','o',' ','e','v','e','r','y' 
               ,'o','n','e',' ', 'w','e','l','c','o','m','e','!'};
  // find first element and point to it.
//  auto data = &message.data()[0]; // or equally 'message.data()';
  auto ptr   = message.begin();
  auto end   = message.end(); // last element
  for(/* empty */ ; ptr != end ; ++ptr){
    std::print("{}",*ptr);        // or std::cout << *ptr
  }
  std::println();






  return 0;
}
