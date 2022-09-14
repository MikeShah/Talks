// @file array.cpp
// g++ -std=c++17 array.cpp -o prog
#include <iostream>
#include <array>

int main(){

    short array[6];
    for(int i=0; i < 6; i++){
        array[i] = i;
    }  
    // Note: Here's a modern C++ 
    //       std::array container
    // std::array<short,6> test;
    // test.fill(1);
    return 0;
}


