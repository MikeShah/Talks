// add.cpp
#include <cstdio>

// Function declaration and 
// definition for 'add'
int add(int a, int b){
	return a+b;
}

// Entry point to program
int main(){

	// One callsite of 'add' below
	int result = add(7,2);

	std::printf("result:%d\n",result);

	return 0;
}

