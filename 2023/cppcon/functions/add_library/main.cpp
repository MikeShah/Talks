// add_library/main.cpp
#include <iostream>
// include 'add.hpp' from local dir.
#include "add_static.hpp"

int main(){
	std::cout << add(7,2) << std::endl;
	return 0;
}


