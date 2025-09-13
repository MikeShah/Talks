// @file: explicit_types2.cpp
// Build and run
// g++-14 -std=c++23 explicit_types2.cpp -o prog && ./prog
#include <iostream>
#include <string>
#include <map>
#include <print>

int main(int argc, char* argv[]){
  // An 'ordered' map
  // Note: I use 'using' in this example so that it's easier
  //       later on with my '::iterator', or otherwise if I want
  //       to change the type to something like unordered_map..
  using StringIntMap = std::map<std::string, int>;
  StringIntMap myMap {  {"Mike",123},
                        {"Bjarne", 234},
                        {"Walter", 345},
                     };

  // Iterators defined with a for-loop
  for(StringIntMap::iterator iter = myMap.begin() ; // init
       iter != myMap.end() ;                        // condition
       iter++)                                      // expression
  {
    std::println("key: {} value: {}", iter->first, iter->second); 
  }
  std::println();

  return 0;
}
