// @file leak.cpp
// g++ -std=c++17 leak.cpp -o prog
#include <iostream>
#include <array>

int main(){

    // Not the worse thing, but bad...
    int* memory = new int [1000];

//    while(1){
        // Very bad...lots of allocations
//        int* lotsOfAllocation = new int [1];
//    }

    return 0;
}

// Eventually the operating system cleans up
// the memory after execution....I hope :)


