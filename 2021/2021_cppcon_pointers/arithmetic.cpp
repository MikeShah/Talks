// @file arithmetic.cpp
// g++ -std=c++17 arithmetic.cpp -o prog
#include <iostream>
#include <array>

int main(){

    short array[6];
    for(int i=0; i < 6; i++){
        array[i] = i;
    }  
    // Pointer to start of array
    short* p_s = &array[0];
    for(int i=0; i < 6; i++){
        std::cout << "*p_s= " << *p_s << std::endl;
        p_s++;
    }

    return 0;
}


