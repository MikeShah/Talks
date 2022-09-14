// @file passByPointerExcessively.cpp
// g++ -std=c++17 passByPointerExcessively.cpp -o prog
#include <iostream>

// Silly example that adds 3 input parameters and
// sets it as an output.
// The 3 inputs are consumed and set to 0.
void passByPointerExcessively(int* out, int* in1, int* in2, int* in3){
    *out = *in1 + *in2 + *in3;
    *in1 = 0;
    *in2 = 0;
    *in3 = 0;
}

int main(){
    int x = 5;    int y = 6;    int z = 7;
    int out;

    passByPointerExcessively(&out,&x,&y,&z);
    std::cout << "out is  : " << out << std::endl; 
    std::cout << "x is now: " << x << std::endl; 
    std::cout << "y is now: " << y << std::endl; 
    std::cout << "z is now: " << z << std::endl; 
        
    return 0;
}


