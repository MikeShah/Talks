// @file arithmetic2.cpp
// g++ -std=c++17 arithmetic2.cpp -o prog
#include <iostream>
#include <array>

int main(){

    short array[6];
    for(int i=0; i < 6; i++){
        array[i] = i;
    }  
    // Array offset shorthand
    std::cout << "array[0]:" << *(array+0) << std::endl;
    std::cout << "array[1]:" << *(array+1) << std::endl;
    std::cout << "array[2]:" << *(array+2) << std::endl;
    std::cout << "array[3]:" << *(array+3) << std::endl;
    std::cout << "array[4]:" << *(array+4) << std::endl;
    std::cout << "array[5]:" << *(array+5) << std::endl;

    return 0;
}


