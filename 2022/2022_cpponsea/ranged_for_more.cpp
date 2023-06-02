// ranged_for_more.cpp
// g++ -std=c++20 ranged_for_more.cpp -o prog
#include <iostream>
#include <vector>
#include <limits>

void sort(std::vector<int> numbers){
    // your favorite sort here...
}

int main(){

    std::vector<int> collection;
    // Populate with some more values for a test
    for(int i=-10; i < 10; ++i){
        collection.push_back(i);
    }

    // Validate our data is clean 
    for(size_t i=1; i < collection.size(); i++){
        if(collection.at(i-1) > collection.at(i)){
            std::cout << "Data is not sorted" << std::endl;
            // Run sorting operation
            sort(collection);
        }
    }

    // Remove negative values
    // Also -- store the min and max because we'll need
    //         that later to normalize the data
    int min = std::numeric_limits<int>::max(); 
    int max = std::numeric_limits<int>::min(); 
    for(std::vector<int>::iterator it = collection.begin();
                                   it != collection.end();
                                   ++it){
        if(*it < 0){
            collection.erase(it-1);
            continue;
        }
        // Compute the min and max from values that were not erased
        min = std::min(min,*it);
        max = std::max(max,*it);
    }
    // Compute the range for normalizing values later
    int range = max-min;
    std::cout << "max: " << max << std::endl;
    std::cout << "min: " << min << std::endl;
    std::cout << "range: " << range << std::endl;
    
    // count outliers in our data set
    // And normalie and store data in a new vector.
    unsigned int outliers= 0;
    std::vector<int> results;
    for(const int& element: collection){
        
        if(element %2 ==0){
            outliers+= 1;
        }else{
            results.push_back( element);
        }    
    }
    std::cout << "outliers:" << outliers << std::endl;
    // Display normalized results
    for(const int& element: results){
        std::cout << element << " normalized: "<< (float)element/(float)range << std::endl;
    }

    return 0;
}
