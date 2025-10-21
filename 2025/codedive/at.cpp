// @file: at.cpp
#include <vector>
#include <print>

int main(){

	std::vector v{0,1,2,3,4,5,6};

	v[7] = 8;
	std::println("This might actually print if capacity is large enough!");
	std::println("{}",v[7]); 

	std::println("This however will always throw an error");
	v.at(7);

	return 0;
}
