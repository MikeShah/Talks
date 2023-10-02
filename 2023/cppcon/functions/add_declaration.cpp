// add_declaration.cpp
#include <cstdio>

// Function declaration 
int add(int,int);

// Entry point to program
int main(){

	// One callsite of 'add' below
	int result = add(7,2);

	std::printf("result:%d\n",result);

	return 0;
}

// Function Definition
int add(int a, int b){
	return a+b;
}
