// g++ -g -std=c++20 stackmemory2.cpp -o prog
#include <iostream>
int main(){

    int x= 42;
    int y= 42;
    std::cout << &x << '\n';
    std::cout << &y << '\n';

    return 0;
}

