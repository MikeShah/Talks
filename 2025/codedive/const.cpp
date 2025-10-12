// @file: const.cpp
// g++ const.cpp -o prog
#include <iostream>
#include <vector>

struct Type{
	int mField;
	// (1) Const on member functions
	decltype(mField) GetField() const{
		// this.mField = 42; // This is illegal
		return mField;
	}
};

// (2) const as input (often use with pass-by-reference)
long SumElements(const std::vector<long>& input){
	long sum{0};
	for(auto i: input){
		sum += i;
	}
	return sum;
}

int main(){
	// (3) Const variables
    const float PI = 3.141526;
    std::cout << PI << std::endl;
	// PI = -42; // This is illegal

	std::vector<long> v{1,3,5,7,9};
	// No copy made of elements, only accessed as 'const'
	std::cout << SumElements(v) << std::endl;

    return 0;
}
