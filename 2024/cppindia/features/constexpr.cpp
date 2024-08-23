// @file constexpr.cpp
// Compile and run: g++ -std=c++23 constexpr.cpp -o prog && ./prog
#include <array>

// 'auto' useful for supporting 'generic' programming
// Note: Still need to add 'qualifiers' like 'const'
constexpr auto sum(const auto a, const auto b){
    return a + b;
}

int main(){

    // 'static' data is baked into the compiler at compile-time
    // 'constexpr' again 'hints' data is known at compile-time
    // for computation
    static constexpr std::array a{11,33,65,77,99};

    // Computation of all compile-time data
    constexpr auto result = sum(1,a[0]);

    return result;
}

