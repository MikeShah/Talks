// @file passByPointer.cpp
// g++ -std=c++17 passByPointer.cpp -o prog
#include <iostream>

void passByValue(int x){
    x = 9999;
}

void passByPointer(int* intPointer){
    *intPointer = 9999;
}

int main(){
    int x = 5;
    int y = 6;
    passByValue(x);
    std::cout << "x is now: " << x << std::endl; 
    passByPointer(&y);
    std::cout << "y is now: " << y << std::endl; 
        
    return 0;
}


