// g++ -g -Wall -std=c++20 compiletime_factorial.cpp -o prog
#include <cassert>

constexpr int fac(int n)
{
    int result = 1;
    for (int i = 2; i <= n; ++i){
			 result *= i;
		}
    return result;
}

// Entry point to program
int main(int argc, char* argv[]){

		static_assert(fac(5) == 120 && "compile-time check");
	
    return 0;
}

