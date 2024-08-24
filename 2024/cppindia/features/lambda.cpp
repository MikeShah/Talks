// @file lambda.cpp
// Compile and run: g++ -std=c++23 lambda.cpp -o prog && ./prog
#include <iostream>
#include <vector>
#include <algorithm>
#include <print>
#include <ranges>

int main(){

    std::vector v{1,3,5,7,9};
    // Local lambda function
    auto square = [](int x){
            return x*x;
            };

    // Anotehr local lambda function
    auto printer = [](int elem){
        std::println("{}",elem);
    };

    // Modify the 'view' of the data
    // Much of the STL uses unary or binary functions to change behavior.
    // Lambdas are thus very convenient to pass or directly instantiate.
    //
    // Note: Use std::ranges::copy if you want to 'keep' the data
    std::ranges::for_each(std::views::transform(v,square),printer);
    // Just print the original data
    std::ranges::for_each(v,printer);
	
    return 0;
}

