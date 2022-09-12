// macro.cpp
// g++ -std=c++17 macro.cpp -o macro

#include <iostream>

// Note the '\' allows us to use multiple lines
#define PRINT(x,line,file) \
    std::cout << file << ":" << line << ": "; \
    std::cout << "value is: " << (x) << "\n";  


int main(){
    
    float PI = 3.1415;
 
    PRINT(PI,__LINE__,__FILE__) 

    return 0;
}
