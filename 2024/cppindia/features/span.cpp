// @file span.cpp
// Compile and run: g++ -std=c++23 span.cpp -o prog && ./prog
#include <iostream>
#include <span>
#include <array>
#include <vector>

// Will always be a dynamic extent. You can assign (or pass) a static extent to
// a dynamic one, but not the other way around.
// If you want this function to preserve 'span' extent, then make it a template
// e.g.
//	template<typename T, int size>
//	void PrintIntData(std::span<T,size> param){
void PrintIntData(std::span<int> param){
	std::cout << param.extent << std::endl;
    if(param.extent == std::dynamic_extent){
        std::cout << "My extent is dynamic (by default) " << std::endl;
    }else{
        std::cout << "Nt extent is static " << std::endl;
    }

	std::cout << "My size is:" << param.size() << std::endl << "\t";
    for(auto& elem: param){
        std::cout << elem << ",";
    }
	std::cout << "\n\n";
}

int main(){

	// Create fixed-size array
    std::array<int, 5> arr = {2,4,6,8,10};
	// Span 'wraps' the 'array'
    std::span<int,5> mySpan{arr};
	// The 'extent' is the static size. 
	// If the extent is 'dynamic' it will be a large integer
	std::cout << mySpan.extent << std::endl;

	// Can pass array (of any size) or span into function
    PrintIntData(arr);
    PrintIntData(mySpan);
    PrintIntData(mySpan.subspan(1,3));

    std::vector<int> myVector = {1,2,3,4,5,6,7};
    PrintIntData(std::span(myVector.begin(),3));
    PrintIntData(myVector);

    return 0;
}
