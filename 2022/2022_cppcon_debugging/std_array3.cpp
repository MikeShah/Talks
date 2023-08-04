/////////////////////////////////////////////////
// Compile with: g++ -std=c++17 std_array3.cpp -o prog
// Run with    : ./prog
//
// Compile for debugging with:
// g++ -std=c++17 -g std_array3.cpp -o prog
// Run with gdb: gdb ./prog --tui
/////////////////////////////////////////////////

// @file std_array3.cpp
// Bring in a header file on our include path
// this happens to be in the standard library
// (i.e. default compiler path)
#include <iostream>
#include <array>    // Include the array library

// Entry point to program 'main' function
int main(int argc, char* argv[]){

    // The first parameter is the type
    // The second parameter is the 'fixed size' of
    // the array. i.e. how many elements we can store.
    std::array<int,5> myArray;

    // We can access an array wit the index operator,
    // that is the []'s
    myArray[0] = 7;
    // We can use member functions in our array as well
    // with the .at(position)
    myArray.at(0) = 9;

    // Some other member functions.
    // Let's test what they return in GDB!
    myArray.front();
    myArray.back();
    myArray.size();
    myArray.max_size();

    return 0;
}
