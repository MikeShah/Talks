// @file: static_cast.cpp
// g++ -std=c++11 static_cast.cpp -o prog
#include <iostream>
#include <cstdint>

int main(){

    static_assert(sizeof(int)==4, "must be a 32-bit architecture");
    static_assert(sizeof(int32_t)==4, "needs a 32-bit fixed width type");
    static_assert(sizeof(int32_t)==sizeof(int), "I may want to safely assume a int is always 4 bytes, but I should always check!");

    int 	primitive_int   = 5;
    int32_t fixed32_int		= 7;

    // When to use fixed-types?
    // When I definitely know the range -- for example pixel formats.
    uint8_t red   = 255;
    uint8_t blue  = 5;
    uint8_t green = 0;
    uint8_t alpha = 127;

    std::cout << "uint8_t min: " << 0 << std::endl;
    std::cout << "uint8_t max: " << UINT8_MAX << std::endl;
	// static_cast available in C++11, easier to grep for
    std::cout 	<< static_cast<short>(red) 	<< "," 
				<< static_cast<short>(green) 	<< "," 
				<< static_cast<short>(blue)   	<< "," 
				<< static_cast<short>(alpha) 	<< std::endl;

    return 0;
}
