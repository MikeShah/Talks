// g++ -g -Wall -std=c++20 static.cpp -o prog
// Dump assembly with:
// g++ -g -Wall -std=c++20 static.cpp -S (And see static.s)
#include <cassert>

static long long lookup_factorials[]= {
	1,2,6,24,120,720,5040,40320,362880,3628800
};


// Entry point to program
int main(int argc, char* argv[]){

		assert(lookup_factorials[5] == 720 && "compile-time check");
	
    return 0;
}

