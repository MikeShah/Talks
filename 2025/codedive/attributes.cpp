// @file: attributes.cpp
// g++ -std=c++11 attributes -o prog
#include <iostream>

[[deprecated]]	// This will produce a 'warning message'
void OldWay(){ }

void work() { std::cout << "work\n"; }

void FallThrough(int input){
	switch(input){
		case 0:
			[[fallthrough]];
		case 1:
			std::cout << "fall is okay here too";
			[[fallthrough]];
		case 2:
			// Should get warning
		default:
			std::cout << "default\n";
	}
}

[[nodiscard]] // More explicit than -Wunused-result
int Meaningful_Value_Generated(){ return 42; }

int main(){

	OldWay();

	Meaningful_Value_Generated(); // Will trigger error if we don't store
								  // return value.
	return 0;
}
