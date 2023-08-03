// g++ -g -Wall -std=c++20 specialization.cpp -o prog && ./prog
#include <iostream>
#include <vector>
#include <numeric>

// Generic n-dimensional mathematical vector
template<typename T, size_t length>
struct VecN{
	// ========== Member Variables ==============
	// Store indidividual components
	//std::vector<T> components;
	T components[length];
	
	// ========== Member Functions ==============
	// Constructor
	VecN();
	// Print out the components 
	void Print();
	// Add some components
	VecN<T,length>& operator+=(const VecN<T,length>& rhs);
};

// Constructor
template<typename T, size_t length>
	VecN<T,length>::VecN(){
	// Initialize components 
	for(size_t i=0; i < length; ++i){
		components[i] = i;
	}
}

template<typename T, size_t length>
void VecN<T,length>::Print(){
	for(size_t i=0; i < length; ++i){			
		std::cout << components[i] << "." << std::endl;
	}
}

// generic addition overload
template<typename T, size_t length>
	VecN<T,length>& VecN<T,length>::operator+=(const VecN<T,length>& rhs){
		for(size_t i=0; i < length; ++i){
		components[i] += rhs.components[i];
	}
	return *this;
}

// Add a specialization with '3' integers
template<>
VecN<int,3>& VecN<int,3>::operator+=(const VecN<int,3>& rhs){
	components[0] += rhs.components[0];
	components[1] += rhs.components[1];
	components[2] += rhs.components[2];

	return *this;
}


// Entry point
int main(){

	VecN<int,3> threeDimensions;
	VecN<int,3> add3;
	for(int i=0; i < 1000000 ; i++){
		threeDimensions += add3;
	}
	threeDimensions.Print();


	return 0;
}
