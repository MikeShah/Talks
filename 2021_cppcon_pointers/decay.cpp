// @file decay.cpp
// g++ -std=c++17 decay.cpp -o prog
#include <iostream>
#include <array>

int main(){

    short array[6];
    for(int i=0; i < 6; i++){
        array[i] = i;
    }  
    // Pointer to start of array
    // Note: 'array' versus '&array[0]
    //       is slightly different.
    std::cout << "sizeof(array)    : " << sizeof(array) << std::endl;
    std::cout << "sizeof(&array[0]): " << sizeof(&array[0]) << std::endl;

    short* p_s = array; // Can just point to the pointer, intead of &array[0]
    for(int i=0; i < 6; i++){
        std::cout << "*p_s= " << *p_s << std::endl;
        p_s++;
    }

    return 0;
}


