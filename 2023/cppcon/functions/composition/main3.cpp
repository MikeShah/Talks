// main3.cpp
#include <iostream>
#include <array>
#include <cassert>

//#include "math_constexpr.hpp"
namespace mike{
		constexpr int add(const int a, const int b){	return a+b; }
		constexpr int sub(const int a, const int b){ 	return a-b; }
		constexpr int mul(const int a, const int b){ 	return a*b; }
}

constexpr int dotProduct(const std::array<int, 3> a, 
								  			 const std::array<int, 3> b){
	// Use our specific call to 'add'
	using namespace mike;
	// Initial sum
	int term1 = mul(a[0],b[0]);
	int term2 = mul(a[1],b[1]);
	int term3 = mul(a[2],b[2]);

	return add(add(term1,term2),term3);
}

int main(){

	const std::array<int,3> v1{1,2,3};
	const std::array<int,3> v2{2,4,6};
	static_assert(v1.size() == v2.size(),"v1.size()!=v2.size() ");

	std::cout << dotProduct(v1,v2) << std::endl;

	return 0;
}


