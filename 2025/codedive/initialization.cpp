// @file: initialization.cpp
// g++ -std=c++23 initialization.cpp -o prog
#include <print>
#include <vector>

float returnFloat(){
	return 3.14f;
}

int main(){

	int a{};
	int b{0};
//	int c{3.14};			// Not allowed!
	int d(3.14);			// Allowed, but implicit conversion to int silently.
	int e{returnFloat()};	// Allowed, but produces warning.
//	std::vector<int> v{1.24,3.51,133.3}; // Not allowed, narrowing conversion 

	std::println("a {}",a);
	std::println("b {}",b);
//	std::println("c not allowed");
	std::println("d truncated to {}",d);
	std::println("e truncated to {} with warning",e);
//	std::println("v not allowed {}",v);

	return 0;
}
