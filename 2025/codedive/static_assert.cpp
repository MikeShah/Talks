// @file: static_assert.cpp
// g++ -std=c++11 static_assert.cpp -o prog
#include <iostream>
#include <cassert>

constexpr int add(int a, int b){
    return a+b;
}

int main(){

	// Works with constexpr
    static_assert(add(2,2)==4, 		  "2+2=4");
	// Works with types
    static_assert(sizeof(int)==4, 	  "int is 4 bytes on this architecture");
	// Enforce fixed-width types
    static_assert(sizeof(int32_t)==4, "int32_t is always 4 bytes");

    return 0;
}
