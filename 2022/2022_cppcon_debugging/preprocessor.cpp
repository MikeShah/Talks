// preprocessor.cpp
// g++ -std=c++17 preprocessor.cpp -o preprocessor

#include <iostream>


int main(){
    
    float PI = 3.1415;

    #ifdef _DEBUG
        std::cout << "Pi is:" << PI << "\n"; 
    #endif

    return 0;
}
