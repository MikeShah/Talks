// iterator.cpp 
#include <iostream>
#include <vector>
#include <algorithm>

int Generate(){
    static int i=0;
    return ++i;
}

int main(){
    
    // Generic collection
    std::vector<int> v1;

    // Algorithm to generate '5' values from a function
    std::generate_n(std::back_inserter(v1), 5, Generate);

    // 'Filter' elements by copying any value greater 
    // than '2' to a new collection.
    std::vector<int> results;
    std::copy_if(v1.begin(),v1.end(),std::back_inserter(results),
                 [](int x){
                    return x > 2; 
                 });

    // Range-based for loop to output results 
    for(auto elem: results){
        std::cout << elem << std::endl;
    }

    return 0;
}
