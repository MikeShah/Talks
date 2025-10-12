// @file: constexpr.cpp
// g++ -std=c++11 constexpr.cpp -o prog
// Just compile this one, no need to run it!
#include <iostream>
#include <cassert>

constexpr int constexpr_add(int a, int b){
    return a+b;
}

int runtime_add(int a, int b){
    return a+b;
}

int main(){

	// This can be caught at compile-time
	static_assert(constexpr_add(7,16) == 24,   "caught at compile-time!");
	// This cannot be caught at compile-time because the function is non-constexpr
	static_assert(runtime_add(7,16)   == 24 && "not caught at compile-time!");
	// This will be caught at run-time when running te function
	assert(		  runtime_add(7,16)   == 24 && "caught at run-time only!");

    return 0;
}
