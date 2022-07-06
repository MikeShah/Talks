// par.cpp
// g++ -std=c++20 par.cpp -o prog
#include <iostream>
#include <vector>
#include <algorithm> 
#include <numeric> 
#include <execution>

int main(){

    std::vector<int> collection(100);
    // Populate
    std::iota(collection.begin(),collection.end(),0);
    // Parallel operaition
    std::transform(std::execution::par,collection.begin(),collection.end(),[](int n){ return n*n;});
    

    return 0;
}   


