// @file dereference.cpp
// g++ -std=c++17 dereference.cpp -o prog
#include <iostream>

int main(){
    // Initialize integer
    int x= 7;
    // Pointer assigned to store address of x
    int* px= &(x);
    // Print out for our understanding
    std::cout << "x value        : " <<  x  << std::endl;
    std::cout << "x address      : " << &x  << std::endl;
    std::cout << "px points to   : " << px  << std::endl;
    std::cout << "px dereferenced: " << *px << std::endl;
        
    return 0;
}


