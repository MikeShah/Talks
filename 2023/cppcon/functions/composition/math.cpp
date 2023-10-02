// math.cpp
#include "math.hpp"

// Group functions into block
namespace mike{ 
		int add(int a, int b){	return a+b; }
		int sub(int a, int b){ 	return a-b; }
}
// Can also use 'scope ::' operator
// I prefer to put all in same block
int mike::mul(int a, int b){ 	return a*b; }

// etc...
//
int math_add(int a, int b){	return a+b; }
int math_sub(int a, int b){ 	return a-b; }
int math_mul(int a, int b){ 	return a*b; }
