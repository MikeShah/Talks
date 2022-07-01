// vector4.cpp
// g++ -std=c++20 vector4.cpp -o prog
#include <iostream>
#include <vector>

int main(){

    std::vector<int> collection {1,2,3};
    collection.push_back(4);

    for(size_t i=0; i < collection.size(); ++i){
        std::cout << collection[i] << std::endl;
    }

    return 0;
}   



