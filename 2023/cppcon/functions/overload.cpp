// overload.cpp
#include <iostream>

// Two square functions with same name
// and different arguments
int square(int x){
	return x * x;
}

int square(int x, bool check){
	if (check && x <0 ){
		std::cout << "Do some logging...\n";
	}
	return x * x;
}

int main(){

	std::cout << square(-5) << std::endl;
	std::cout << square(-5, true) << std::endl;


	return 0;
}
