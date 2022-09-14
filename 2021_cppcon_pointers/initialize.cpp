// @file initialize.cpp
// g++ -std=c++17 initialize.cpp -o prog
#include <iostream>

int main(){

    int x = 7;
    int* px = &x;

    std::cout << "x is: " << x << std::endl;
    std::cout << "*px is: " << *px << std::endl;

    return 0;
}
