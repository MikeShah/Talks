#include <iostream>
#include <vector>
#include <ranges>

int main(){
	std::vector c{1,2,3,4,5};

     // C-Style loop
     // Nothing wrong with this...
     std::cout << "C-Style Loop" << std::endl;
     for(size_t i=0; i < c.capacity(); ++i){
         std::cout << c[i] << std::endl;
     }
 
     // C++98 style loop with iterators
     std::cout << "C++98 Style iterator Loop" << std::endl;
     for(auto         it = c.begin();
                     it != c.end();
                     ++it){
         std::cout << *it << std::endl;
     }
 
     // Iterators also will give us access to std::algorithm
     std::cout << "std::algorithm Loop" << std::endl;
     std::for_each(c.begin(),c.end(),[](auto &e){
             std::cout << e << std::endl;
     });
 
     // We need to implement iterators however
     // in order to use range-based loops
     std::cout << "ranged-for Loop" << std::endl;
     for(const auto& e : c){
         std::cout << e << std::endl;
     }

	// Range(s) views
	std::cout << "ranges view" << std::endl;
	for(auto elem: std::views::all(c)){
		std::cout << elem << std::endl;
	}

}
