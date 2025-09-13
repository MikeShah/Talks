// @file: vector_iterator.cpp
// Build and run
// g++-14 -std=c++23 vector_iterator.cpp -o prog && ./prog
#include <iostream>
#include <vector>
#include <print>

int main(int argc, char* argv[]){

  std::vector message {'H','e','l','l','o',' ','e','v','e','r','y' 
               ,'o','n','e',' ', 'w','e','l','c','o','m','e','!'};
  // find first element and point to it.
//  auto data = &message.data()[0]; // or equally 'message.data()';
  auto ptr   = std::begin(message);
  auto end   = std::end(message); // last element
  for(/* empty */ ; ptr != end ; ++ptr){
    std::print("{}",*ptr);        // or std::cout << *ptr
  }
  std::println();






  return 0;
}
