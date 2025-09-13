// @file: algorithms2.cpp
// Build and run
// g++-14 -std=c++23 algorithms2.cpp -o prog && ./prog
#include <iostream>
#include <string>
#include <vector>
#include <print>

template <typename T>
void PrintCollection(const T& collection, std::string note=""){
  println("{}",note);
  for(const auto& elem : collection){
    std::print("{} ",elem); 
  }
  std::println();
}

int main(int argc, char* argv[]){
  // (0) Initial data
  std::vector<std::string> v{"B","C","D","G", "F", "E", "A"};

  PrintCollection(v,"=== Before ==="); // (1) Before our work
  std::sort(v.begin(),v.end());        // (2) Perform algoritm
  PrintCollection(v,"=== After ===");  // (3) View results


  return 0;
}
