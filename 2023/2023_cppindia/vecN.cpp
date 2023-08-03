// g++ -g -Wall -std=c++20 vecN.cpp -o prog && ./prog
#include <iostream>
#include <vector>

// Generic n-dimensional mathematical vector
template<typename T>
struct VecN{
	// ========== Member Variables ==============
	// Store indidividual components
	std::vector<T> components;
	
	// ========== Member Functions ==============
	// Constructor
	VecN(size_t elements);
	// Print out the components 
	void Print() const;
	// Add some components
	VecN<T>& operator+=(const VecN<T>& rhs);
};

// Constructor
template<typename T>
	VecN<T>::VecN(size_t elements){
	// Initialize components 
	for(size_t i=0; i < elements; ++i){
		components.push_back(i);
	}
}

// Print
template<typename T>
void VecN<T>::Print() const{
	for(size_t i=0; i < components.size(); ++i){			
		std::cout << components.at(i) << "." << std::endl;
	}
}

// generic addition overload
template<typename T>
	VecN<T>& VecN<T>::operator+=(const VecN<T>& rhs){
		for(size_t i=0; i < components.size(); ++i){
		components[i] += rhs.components[i];
	}
	return *this;
}



// Entry point
int main(){

	VecN<int> threeDimensions(3);
	VecN<int> add3(3);
	for(int i=0; i < 1000000; ++i){
		threeDimensions += add3;
	}
	threeDimensions.Print();


	return 0;
}
