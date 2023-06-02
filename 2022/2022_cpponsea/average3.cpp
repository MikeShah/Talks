// average3.cpp
// g++ -std=c++20 average3.cpp -o prog
#include <iostream>
#include <vector>

void SortIntVector(std::vector<int>& input){
    // Choose your favorite algorithm...
    int i=1;
    while(i < input.size()){
        int j=i;
        while(j>0 && input[j] < input[j-1]){
                std::swap(input[j-1],input[j]);
                j=j-1;
        }
        i=i+1;
    } 
}

int main(){

    std::vector<int> collection {-1,1,-2,2,-3,3,-4,4,-5,5};
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

    SortIntVector(result_collection);

    float Top3Sum =  result_collection[result_collection.size()-1] 
                   + result_collection[result_collection.size()-2]
                   + result_collection[result_collection.size()-3];

    std::cout << "Average of Positive Values: "
              << Top3Sum/3.0f
              << std::endl;

    return 0;
}   


