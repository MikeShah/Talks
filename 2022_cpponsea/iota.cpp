// iota.cpp
// g++ -std=c++2b iota.cpp -o prog
#include <iostream>
#include <vector>
#include <algorithm> 
#include <numeric> 
#include <random>

int main(){

    std::vector<int> collection(10);
    // Fill in range with successive elements
    std::iota(collection.begin(), collection.end(),-5);
    // Shuffle the range
    std::random_device randomDevice;
    std::mt19937 randGenerator{randomDevice()};
 
    std::ranges::shuffle(collection, randGenerator);

    for(const int& element : collection){
        std::cout << element << std::endl;
    }

    return 0;
}   


