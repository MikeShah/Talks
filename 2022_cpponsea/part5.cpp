// part5.cpp
// g++ -std=c++20 part5.cpp -o prog
#include <iostream>
#include <vector>
#include <limits>

#include <numeric>   // HURRAY!
#include <algorithm> // HURRAY!

int main(){

    std::vector<int> collection(20);
    // Populate with some more values for a test
    std::iota(collection.begin(),collection.end(),-10);

    // Validate our data is clean 
    if(!std::is_sorted(begin(collection),end(collection))){
        std::sort(begin(collection),end(collection));
    }

    // Remove negative values
    std::remove_if(begin(collection),end(collection), [](int n){ return n < 0;});

    const auto [min,max] = std::minmax_element(begin(collection),end(collection));

    int range = *max - *min;
    std::cout << "max: " << *max << std::endl;
    std::cout << "min: " << *min << std::endl;
    std::cout << "range: " << range << std::endl;
    
    // count outliers in our data set
    // And normalie and store data in a new vector.
    std::vector<int> results;
    auto outliers = std::count_if(begin(collection),
                                 end(collection),[](int n){
                                 return n%2==0; });

    std::transform(begin(collection),end(collection),results.begin(),
                       [](int n){
                       return n%2==1; }
                   );
                  
    std::cout << "outliers:" << outliers << std::endl;
    // Display normalized results){

    auto println = [](auto element){ 
                        std::cout << element << " normalized: "<< element << std::endl;
    };

    for_each(begin(collection),end(collection),println);

    return 0;
}
