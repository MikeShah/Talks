// @file auto.cpp
// Compile and run: g++ -std=c++23 auto.cpp -o prog && ./prog
#include <print>
#include <vector>

// 'auto' useful for supporting 'generic' programming
// Note: Still need to add 'qualifiers' like 'const'
auto sum(const auto a, const auto b){
    return a + b;
}

int main(){
 
    // Not a good use of auto, unclear if short, long, int, etc
    // auto integer = 7;
    std::vector v{1,3,5,7,9};

    // Use of 'auto' here useful to deduce underlying type
    // in collection
    for(auto elem: v){
        std::println("{}",sum(elem,1));
    }

    // 'auto' useful for 'redudant' or 'long' declarations
    //  std::vector<int>::iterator start= v.begin(); 
    auto start = v.begin(); // This is fine

    return 0;
}
