// deque.cpp
#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>

int main(){

    // Double-ended queue
    // Usually implemented as links of 
    // fixed-size arrays
    std::deque<int> d{1,2,3,4};

    // Ability to push on front and back quickly!
    d.push_back(123);
    d.push_front(999);

    // Prints out 999,1,2,3,4,123
    auto print = [](int a){ std::cout << a << ","; };
    std::for_each(d.cbegin(),d.cend(), print);

    return 0;
}
