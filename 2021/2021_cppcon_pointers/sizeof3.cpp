// @file sizeof3.cpp
// g++ -Wall -Wextra -std=c++17 sizeof3.cpp -o prog
#include <iostream>
#include <cstdint>   // Fixed width integer types (c++11)

struct UserDefinedType{
    int x,y,z;  // 12 bytes 
    char a,b,c; // 3 more bytes
    // +1 more bytes for padding
    // (Don't assume!)
};

int main(){
    
    std::cout << "sizeof(bool)           :" << sizeof(bool) << std::endl;
    std::cout << "sizeof(unsigned char)  :" << sizeof(unsigned char) << std::endl;
    std::cout << "sizeof(char)           :" << sizeof(char) << std::endl;
    std::cout << "sizeof(short)          :" << sizeof(short) << std::endl;
    std::cout << "sizeof(uint8_t)        :" << sizeof(uint8_t) << std::endl;
    std::cout << "sizeof(int)            :" << sizeof(int) << std::endl;
    std::cout << "sizeof(float)          :" << sizeof(float) << std::endl;
    std::cout << "sizeof(double)         :" << sizeof(double) << std::endl;
    std::cout << "sizeof(UserDefinedType):" << sizeof(UserDefinedType) << std::endl;

    return 0;
}

