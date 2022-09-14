// @file new.cpp
// g++ -std=c++17 new.cpp -o prog
#include <iostream>

int main(){
    // Request enough bytes for: sizeof(int)*3
    // intArray points to the start of that
    // chunk of memory i.e.,
    // intArray = &(block of memory)
    int* intArray = new int[3];

    // Delete the entire array
    // Note: We use brackets to delete the entire
    //       allocated block.
    //       Using only 'delete' removes the first
    //       element.
    delete[] intArray;

    return 0;
}


