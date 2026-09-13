// @file: process.cpp
#include <print>

int add(int x, int y){
    return x+y;
}

int main(){

    int a = 5;
    int b = 6;
    std::println("{}",add(a,b));

    int* a2 = new int;
    int* b2 = new int;
    *a2 = 7; *b2 = 8;
    std::println("{}",add(*a2,*b2));
    
    delete a2; delete b2;

    return 0;
}
