// average_algorithm_partition.cpp
// g++ -std=c++20 average_algorithm_partition.cpp -o prog
#include <iostream>
#include <vector>
#include <algorithm> // NEW LIBRARY (for copy_if)
#include <numeric> // NEW LIBRARY (for accumulate)

int main(){

    std::vector<int> collection {-1,1,-2,2,-3,3,-4,4,-5,5};
    
    auto secondGroupIterator = std::partition(collection.begin(),
                                              collection.end(),
                                              [](int n){ return n < 0;});

    if(!std::is_sorted(secondGroupIterator,collection.end()))
        std::sort(secondGroupIterator,collection.end());

    int sum = std::accumulate(end(collection)-3,end(collection),0);

    std::cout << "Average of Positive Values: "
              << (float)sum/3.0f
              << std::endl;

    return 0;
}   


