// @file stdfunction.cpp
// g++ -std=c++17 stdfunction.cpp -o prog
#include <iostream>
#include <functional> // std::function

int add(int x,int y){
    return x+y;
}
int multiply(int x, int y){
    return x*y;
}

int main(){
    // Use the modern std::function
    std::function<int(int,int)> f_arithmetic = add;
    // Point to the add function
    f_arithmetic = add;
    std::cout << "f_arithmetic(2,7) = " << f_arithmetic(2,7) << std::endl;
    // Point to the multiply function
    f_arithmetic = multiply;
    std::cout << "f_arithmetic(2,7) = " << f_arithmetic(2,7) << std::endl;

    return 0;
}


