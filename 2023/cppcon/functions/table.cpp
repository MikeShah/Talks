// table.cpp
#include <iostream>
#include <vector>
#include <functional>

int add(int x,int y)			{ 	return x+y; }
int multiply(int x, int y){  	return x*y; }

int main(){
	
		std::function<int(int,int)> operations[2];
		
		operations[0] = add;
		operations[1] = multiply;

		for(auto op: operations){
			std::cout << op(7,2) << std::endl;
		}

    return 0;
}
