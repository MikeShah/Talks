// default_args.cpp
#include <iostream>

// check is false unless we 
// explicitly pass in a value.  
int square(int x, bool check=false){
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
