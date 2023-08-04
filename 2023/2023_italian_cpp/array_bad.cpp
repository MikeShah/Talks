// g++ -g -Wall -std=c++20 array_bad.cpp -o prog && ./prog
#include <iostream>

// Generic n-dimensional mathematical vector
template<typename T>
struct VecN{
	// ========== Member Variables ==============
	// Store indidividual components
	T* components;
	size_t mSize;
	
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
	mSize = elements;
	// Initialize components 
	components = new T[elements];
	for(size_t i=0; i < elements; ++i){
		components[i] = i;;
	}
}

// Print
template<typename T>
void VecN<T>::Print() const{
	for(size_t i=0; i < mSize; ++i){			
		std::cout << components[i] << "." << std::endl;
	}
}

// generic addition overload
template<typename T>
	VecN<T>& VecN<T>::operator+=(const VecN<T>& rhs){
		for(size_t i=0; i < mSize; ++i){
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
