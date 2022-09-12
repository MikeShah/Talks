// printfdebug3.cpp
// g++ -std=c++17 printfdebug3.cpp -o printfdebug3
#include <iostream>
#include <stdlib.h>

int square(int a){
    return a;
}

int main(){

    while(1){
        
        std::cout << "output 1: " << square(5) << std::endl;
        if(square(5)==25){
            std::cout << "output 2: " << square(5) << std::endl;
            exit(1);
        }
        std::cout << "output 3: " << square(5) << std::endl;
    }

    std::cout << "Exiting program\n";

    return 0;
}
