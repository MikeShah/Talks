// @file dereference3.cpp
// g++ -std=c++17 dereference3.cpp -o prog
#include <iostream>

int main(){
    // Initialize integer
    int x= 7;
    // Pointer assigned to store address of x
    int* px= &(x);
    // What happens if we dereference px
    // and change the value?
    (*px) = 42;
    std::cout << "x's value is: " << x << std::endl;
 
    return 0;
}


