// @file types.cpp
// g++ -std=c++17 types.cpp -o prog
#include <iostream>

int main(){

    int   x= 7;
    char  c= 'a';
    float f= 3.1415;
      
    int*   px= &x;
    char*  pc= &c;
    float* pf= &f;

    std::cout << "x is  : " <<   x << std::endl;
    std::cout << "*px is: " << *px << std::endl;
    std::cout << "sizeof(x) : " << sizeof(x) << std::endl;
    std::cout << "sizeof(px): " << sizeof(px) << std::endl;

    std::cout << "c is  : " <<   c << std::endl;
    std::cout << "*pc is: " << *pc << std::endl;
    std::cout << "sizeof(c) : " << sizeof(c) << std::endl;
    std::cout << "sizeof(pc): " << sizeof(pc) << std::endl;

    std::cout << "f is  : " <<   f << std::endl;
    std::cout << "*pf is: " << *pf << std::endl;
    // In this example, I just explicitly put the type instead
    // of the symbol in the 'sizeof' operator.
    std::cout << "sizeof(float) : " << sizeof(float) << std::endl;
    std::cout << "sizeof(float*): " << sizeof(float*) << std::endl;

    return 0;
}
