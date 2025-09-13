// @file: list_iterator.cpp
// Build and run
// g++-14 -std=c++23 list_iterator.cpp -o prog && ./prog
#include <iostream>
#include <list>
#include <print>

int main(int argc, char* argv[]){

  std::list message {'H','e','l','l','o',' ','e','v','e','r','y' 
               ,'o','n','e',' ', 'w','e','l','c','o','m','e','!'};
  // find first element and point to it.
//  auto data = &message.data()[0]; // or equally 'message.data()';
  auto ptr   = std::begin(message);
  auto end   = std::begin(message);
  std::advance(end,5); // first 'n' elements
  for(/* empty */ ; ptr != end ; ++ptr){
    std::print("{}",*ptr);        // or std::cout << *ptr
  }
  std::println();






  return 0;
}
