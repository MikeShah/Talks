// @file dangling.cpp
// g++ -std=c++17 dangling.cpp -o prog
#include <iostream>

char* dangerouslyReturnLocalValue(){
        char c = 'c';
        return &c;
}

int main(){

    char* danglingPointer1 = dangerouslyReturnLocalValue(); 

    std::cout << "*danglingPointer1 is: " << *danglingPointer1 << std::endl;

    return 0;
}


