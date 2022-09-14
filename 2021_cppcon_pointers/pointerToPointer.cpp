// @file pointerToPointer.cpp
// g++ -std=c++17 pointerToPointer.cpp -o prog
#include <iostream>

int main(){
    // Initialize integer
    int x= 7;
    // Pointer assigned to store address of x
    int* px= &(x);

    int** p_px = &px; // p_px is a pointer to an integer pointer

    // What happens if we dereference p_px
    // and change the value?
    **p_px = 77;

    // Follow two levels of indirection
    std::cout << "x's value is: " << x      << std::endl;
    std::cout << "*px       is: " << *px    << std::endl;
    std::cout << "**p_px    is: " << **p_px << std::endl << std::endl;
    // FYI (Here is one level of indirection)
    std::cout << "*p_px    is: " << *p_px << std::endl;
    std::cout << "&x       is: " << &x << std::endl;
    // FYI (Here is zero levels of indirection)
    std::cout << "p_px     is: " << p_px << std::endl;
    std::cout << "&px      is: " << &px << std::endl;
 
    return 0;
}


