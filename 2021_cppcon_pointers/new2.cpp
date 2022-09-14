// @file new2.cpp
// g++ -std=c++17 new2.cpp -o prog
#include <iostream>

int main(){
    int* intArray = new int[3];
    for(int i=0; i < 3; i++){
        intArray[i] = i;
    }    
    // Let's share our data by pointing
    // to it through another pointer
    int* intArray2 = intArray;
    // Note: When we assign intArray2 to intArray, intArray2 now holds
    //       the same address as intArray.
    std::cout << intArray << " should = " << intArray2 << std::endl;

    std::cout << "intArray2[1]= " << intArray2[1] << std::endl;
    delete[] intArray;

    // Uh-oh, what if we try to work with intArray2
    std::cout << "intArray2[1]= " << intArray2[1] << std::endl;

    return 0;
}


