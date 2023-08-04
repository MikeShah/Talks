// average_algorithm.cpp
// g++ -std=c++20 average_algorithm.cpp -o prog
#include <iostream>
#include <vector>
#include <algorithm> // NEW LIBRARY (for copy_if)
#include <numeric> // NEW LIBRARY (for accumulate)

int main(){

    std::vector<int> collection {-1,1,-2,2,-3,3,-4,4,-5,5};
    
    std::vector<int> result_collection;
    std::copy_if(collection.begin(), collection.end(),
              std::back_inserter(result_collection),
              [](int n){
                return n > 0;
              });

    std::sort(result_collection.begin(),result_collection.end());

    int sum = std::accumulate(end(result_collection)-3,
                              end(result_collection),0);

    std::cout << "Average of Positive Values: "
              << (float)sum/3.0f
              << std::endl;

    return 0;
}   


