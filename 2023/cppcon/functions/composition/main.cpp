// main.cpp
#include <iostream>
#include <array>
#include <cassert>

#include "math.hpp"

int dotProduct(std::array<int, 3> a, 
							 std::array<int, 3> b){
	// Use our specific call to 'add'
	using namespace mike;
	// Initial sum
	int result =0;
	// Assign result to the previous sum, plus
	// the product of each element
	for(int i=0; i < 3; ++i){
		result = add(result,mul(a[i],b[i]));
	}
	return result;
}

int main(){

	std::array<int,3> v1{1,2,3};
	std::array<int,3> v2{2,4,6};
	static_assert(v1.size() == v2.size(),"v1.size()!=v2.size() ");

	std::cout << dotProduct(v1,v2) << std::endl;

	return 0;
}


