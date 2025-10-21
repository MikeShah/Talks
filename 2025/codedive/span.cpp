// @file: span.cpp
#include <iostream>
#include <print>
#include <span>
#include <array>
#include <vector>

// span is non-owning, but can modify elemements
void ModifyFirstElement(std::span<int> param){
	if(param.size()>0){
		param[0] = 100;
	}
	std::println("Print: {}",param);
	
}

int main(){
    // Create a span from a statically sized data type
	std::array<int, 4> array {1,2,3,4};
    std::span mySpan{array};
    ModifyFirstElement(array);

	// Pass in directly a container and use the span
    std::vector<int> myVector = {1,2,3,4,5,6,7};
    ModifyFirstElement(myVector);
    ModifyFirstElement(std::span(myVector.begin(),3));

    return 0;
}

