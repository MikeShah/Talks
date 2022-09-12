// g++ -g -Wall -Wextra -std=c++17 gdb2.cpp -o gdbexample2
#include <iostream>



int main(){

    int counter =0;
    while(1){
        std::cout << "running " << counter << " times\n";
        counter++;
    }

    return 0;
}
