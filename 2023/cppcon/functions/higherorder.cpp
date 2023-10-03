// higherorder.cpp
#include <iostream>
#include <vector>
#include <functional>

int add(int x,int y)			{ 	return x+y; }
int multiply(int x, int y){  	return x*y; }

// First argument original value
// Second argument is always 2.
// Mutates original container.
void ByTwo(std::function<int(int,int)> operation, 
					 std::vector<int>& data){
		
		 for(auto& elem: data){
				elem = operation(elem,2);
		 }
}

int main(){
		std::vector<int> v{1,3,5,7,9,11};

		ByTwo(add,v);
		ByTwo(multiply,v);

		for(auto elem: v){
			std::cout << elem << std::endl;
		}

    return 0;
}
