#include <iostream>
#include <vector>
#include <algorithm>

// [ captures ] ( params )  { body }

struct PrintFunctor{
	int lastResult{-1};
	void operator()(int n){
		lastResult=n;
		std::cout << n << ",";
	}
};

int main(){

  std::vector<int> v{1,3,2,5,9};

	PrintFunctor pf;
	for(auto elem: v){
		pf(elem);
	}


	std::cout << "functor last result:" << pf.lastResult << std::endl;

	int lastResult=-1;
	auto print_v = [&lastResult](int n) {   
											lastResult=n;
											std::cout << n << ",";
	 };

	std::for_each(begin(v), end(v), print_v);

	std::cout << '\n' << lastResult << std::endl;
	
			      
/*
    for(auto element: v){
        std::cout << element << ",";
    }
*/
    std::cout << std::endl;

    return 0;
}

