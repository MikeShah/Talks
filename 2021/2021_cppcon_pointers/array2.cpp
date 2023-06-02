// @file array2.cpp
// g++ -std=c++17 array2.cpp -o prog
#include <iostream>
#include <array>

int main(){

    short array[6];
    for(int i=0; i < 6; i++){
        array[i] = i;
    }  
    // Pointer to element in array
    short* p_s = &array[2];
    std::cout << "&array[2]:" << *p_s << std::endl;
    // Point to another element in array
    p_s = &array[3];
    std::cout << "&array[3]:" << *p_s << std::endl;

    return 0;
}


