// @file functionPointer.cpp
// g++ -std=c++17 functionPointer.cpp -o prog
#include <iostream>

int add(int x,int y){
    return x+y;
}
int multiply(int x, int y){
    return x*y;
}

int main(){
    // Create a pointer to the function
    int (*pfn_arithmetic)(int,int);
    // Point to the add function
    pfn_arithmetic = add;
    std::cout << "pfn_arithmetic(2,7) = " << pfn_arithmetic(2,7) << std::endl;
    // Point to the multiply function
    pfn_arithmetic = multiply;
    std::cout << "pfn_arithmetic(2,7) = " << pfn_arithmetic(2,7) << std::endl;

    return 0;
}


