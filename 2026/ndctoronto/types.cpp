// @file: types.cpp
// g++ -std=c++23 -Wall -Wextra -g types.cpp -o prog
#include <print>

int main(){
  using namespace std;

  int value = 78;
  
  println("value is: {}",value);
  // Different ways to 'change' interpretation of bits
  // C-Style (less preferred)
  println("value is: {}",(char)value);
  // Forced to reinterpret the bits
  println("value is: {}",reinterpret_cast<char*>(&value)); 
  // Preferred C++ style
  println("value is: {}",static_cast<char>(value)); 

  return 0;
}
