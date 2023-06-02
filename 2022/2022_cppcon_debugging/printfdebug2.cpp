// printfdebug2.cpp
// g++ -std=c++17 printfdebug2.cpp -o printfdebug3
#include <iostream>
#include <stdlib.h>

int square(int a){
    return a;
}

int main(){

    while(1){
        if(square(5)==25){
            exit(1);
        }
    }

    std::cout << "Exiting program\n";

    return 0;
}
