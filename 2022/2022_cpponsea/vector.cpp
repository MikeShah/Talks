// vector.cpp
// g++ -std=c++20 vector.cpp -o prog
#include <iostream>
#include <vector>

int main(){

    std::vector<int> collection {1,2,3};
    collection.push_back(4);

    for(int i=0; i < collection.size(); i++){
        std::cout << collection[i] << std::endl;
    }

    return 0;
}   



