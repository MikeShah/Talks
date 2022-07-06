// median.cpp
// g++ -std=c++20 median.cpp -o prog
#include <iostream>
#include <vector>
#include <algorithm> // NEW LIBRARY (for copy_if)
#include <numeric> // NEW LIBRARY (for accumulate)

int main(){

    std::vector<int> collection {-1,1,-2,2,-3,4,-4,4,-5,5};
    
    auto median = collection.begin() + collection.size()/2;
    std::nth_element(collection.begin(),median,collection.end());
    std::nth_element(collection.begin(),median+1,collection.end());
    std::nth_element(collection.begin(),median-1,collection.end());

    float sum = collection[collection.size()/2]
                + collection[collection.size()/2 - 1]
                + collection[collection.size()/2 + 1];

    std::cout << "Median of 3 Positive Values: "
              << sum/3.0f
              << std::endl;

    return 0;
}   


