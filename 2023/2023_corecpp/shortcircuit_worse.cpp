//g++ -g -Wall -std=c++20 shortcircuit_worse.cpp -o prog
#include <iostream>

bool Is_ExpensiveToComputeFunction(){
    bool result = false;
    /*
         ... lots of code ... 
         ... result maybe true or false ...
    */
    std::cout << "I take a really looooong time!\n";
    return result;
}

// Entry point to program
int main(int argc, char* argv[]){

    bool flag = false;

    // Short-circuit evaluation
    if (Is_ExpensiveToComputeFunction() && flag){

    }

    // Not short-circuit evaluated
    if (Is_ExpensiveToComputeFunction() & flag){

    }

    return 0;
}



