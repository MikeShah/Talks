// span.cpp
#include <iostream>
#include <span>

void SetToOne(int* array, int size){
	for(int i=0; i < size; ++i){
		array[i] = 1;	
	}
}

void SetToOne(std::span<int> array){
	for(auto& elem: array){
		elem = 1;
	}
}

// Exercise: Find std::fill :)

int main(){
	
	int stackArray1[5];
	SetToOne(stackArray1,5);

	std::array<int,5> stackArray2;
	std::span<int> mySpan{stackArray2};
	SetToOne(mySpan);


	return 0;
}
