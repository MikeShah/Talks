// g++ -g -Wall -std=c++20 increment.cpp -o prog
#include <cstddef>

struct Graph{
	/*
	 *
	 */
	size_t size() const{
		return 42;
	}	
};


// Entry point to program
int main(int argc, char* argv[]){

		Graph g;

		for(size_t i=0; i < g.size(); i++){
			/* Do some work */ 
		}
		
		// Observe that we 'cache' the size here 
		// so we only have to compute it once.
		const size_t graph_size = g.size();
		for(size_t i=0; i != graph_size; ++i){
			/* Do some work */ 
		}
	
    return 0;
}

