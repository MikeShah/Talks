// @file double.cpp
// g++ -std=c++17 double.cpp -o prog
#include <iostream>


int main(){

    float* f1 = new float[100];
    float* f2 = f1;

    delete[] f2;
    f2 = nullptr;
    delete[] f1;
    // Be good and set f1 to nullptr
    f1 = nullptr;
    // Did I delete f2? I'll try again
    delete[] f2;    

    return 0;
}

