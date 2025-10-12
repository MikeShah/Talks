// @file: assert.cpp
//
// Compile with assertions (and see the assembly)
// g++ -assert.cpp -S && vim assert.s
//
// Compile-out the asserts (and see the assembly)
// g++ -DNDEBUG assert.cpp -S && vim assert.s
#include <iostream>
#include <cassert>

constexpr int add(int a, int b){
    return a+b;
}

int main(){

	// Works with constexpr, checked at run-time
    assert(add(2,2)==4 && 		  "2+2=4");
	// Works with types, checked at run-time
    assert(sizeof(int)==4 && 	  "int is 4 bytes on this architecture");
	// Checked at run-time
    assert(sizeof(int32_t)==4 && "int32_t is always 4 bytes");

    return 0;
}
