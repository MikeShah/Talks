// rangedfor.cpp
// g++ -std=c++20 rangedfor.cpp -o prog
#include <iostream>
#include <vector>

int main(){

    std::vector<int> collection {1,2,3};
    collection.push_back(4);

    for(const int& element : collection){
        std::cout << element << std::endl;
    }

    return 0;
}   



