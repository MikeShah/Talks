// @file: for2.cpp
// Build and run
// g++-14 -std=c++23 for2.cpp -o prog && ./prog
#include <iostream>
#include <string>
#include <print>

int main(int argc, char* argv[]){

  std::string secret_message = "Hello everyone, welcome!";
  int key = 1;
  std::string encoded_message;
  std::string decoded_message;

  // 'caesar cipher' to 'shift' characters
  for(std::size_t i=0; i < secret_message.length(); ++i){
    encoded_message += secret_message[i] + key;
  }
  std::println("encoded_message: {}",encoded_message);

  // 'Run opposite' algorithm to decode
  for(std::size_t i=0; i < secret_message.length(); ++i){
    decoded_message += encoded_message[i] - key;
  }
  std::println("decoded_message: {}",decoded_message);
  return 0;
}
