// g++ -g -Wall -std=c++20 static_assert.cpp -o prog
#include <cassert>

// Entry point to program
int main(int argc, char* argv[]){

		static_assert(sizeof(int)==5091 && "compile-time check");
		assert(sizeof(int)==7091 && "run-time check!");
	
    return 0;
}

