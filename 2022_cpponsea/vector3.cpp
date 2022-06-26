// vector5.cpp
// g++ -std=c++20 vector5.cpp -o prog
#include <iostream>
#include <vector>

int main(){

    std::vector<int> collection {1,2,3};
    collection.push_back(4);

    for(auto element ; collection){
        std::cout << element << std::endl;
    }

    return 0;
}   



