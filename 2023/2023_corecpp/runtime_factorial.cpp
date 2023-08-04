// g++ -g -Wall -std=c++20 runtime_factorial.cpp -o prog
#include <cassert>

int fac(int n)
{
    int result = 1;
    for (int i = 2; i <= n; ++i){
			 result *= i;
		}
    return result;
}

// Entry point to program
int main(int argc, char* argv[]){

		assert(fac(5) == 120 && "compile-time check");
	
    return 0;
}

