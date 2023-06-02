// @file decay3.cpp
// clang++-10 -std=c++20 decay3.cpp -o prog
#include <iostream>
#include <array>

// Kind of a wild example...
// We may want to use a std::vector
template<int T>
void printArrayWithoutSizeParameter(const std::array<short,T>& arr){
    std::cout << "sizeof(arr)  : " << sizeof(arr) << std::endl;
}

int main(){

    std::array<short,11> array;
    array.fill({{0,1,2,3,4,5,6,7,8,9,10}});
    // array.size() is constexpr
    printArrayWithoutSizeParameter<array.size()>(array);

    // Creating another array....
    std::array<short,10> array2;
    printArrayWithoutSizeParameter<10>(array2);

    return 0;
}


