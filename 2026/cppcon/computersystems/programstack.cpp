#include <iostream>
#include <stdlib.h>

int global;
void foo(){}

auto main(int argc, char* argv[], char* env[]) -> int{

    std::cout << "args      : " << &argv[0] << std::endl;
    std::cout << "env       : " << (void*)getenv("HOME") << std::endl;
    int x,y;
    std::cout << "stack 1   : " << &x << std::endl;
    std::cout << "stack 2   : " << &y << std::endl;
    std::cout << "functions : " << (void*)&(foo) << std::endl;
    std::cout << "globals   : " << &global << std::endl;

    int* heap1 = new int;
    int* heap2 = new int;
    std::cout << "heap 1    : " << heap1 << std::endl;
    std::cout << "heap 2    : " << heap2 << std::endl;

    return 0;
}
