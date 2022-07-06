// average2.cpp
// g++ -std=c++20 average2.cpp -o prog
#include <iostream>
#include <vector>

int main(){

    std::vector<int> collection {-3,-2,-1,1,2,3};
    std::vector<int> result_collection;

    int sum= 0;

    for(const int& element : collection){
        // Sum all of the positive elements
        // And put them in a new list
        if(element > 0){
            sum+= element;

            result_collection.push_back(element);
        }
    }

    std::cout << "Average of Positive Values: "
              << (float)sum/(float)result_collection.size()
              << std::endl;

    return 0;
}   


