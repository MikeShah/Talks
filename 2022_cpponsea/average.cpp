// average.cpp
// g++ -std=c++20 average.cpp -o prog
#include <iostream>
#include <vector>

int main(){

    std::vector<int> collection {-3,-2,-1,1,2,3};

    int sum= 0;
    int numberOfElements= 0;
    for(const int& element : collection){
        // Sum all of the positive elements
        // And put them in a new list
        if(element > 0){
            sum+= element;
            numberOfElements+=1;
        }
    }

    std::cout << "Average of Positive Values: "
              << (float)sum/(float)numberOfElements
              << std::endl;

    return 0;
}   


