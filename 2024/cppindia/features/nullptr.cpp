// @file nullptr.cpp
// Compile and run: g++ -std=c++23 nullptr.cpp -o prog && ./prog
#include <print>
#include <vector>


void PointerParam(int* value){ std::print("PointerParam called"); }
void IntegerParam(int value){ std::print("IntegerParam called"); }

int main(){

    // NULL is effectively '0' (zero).
    // These are all 'equivalent'
    // 'pGood' is a nullptr, which is more 'searchable'
    // NULL may however be useful in a 'C-style API'
    int* pGood = nullptr;
    int* pOld  = NULL;
    int* pBad  = 0;
    int integer = 0;

    if(integer ==0){ } // Allowed

    // Not allowed -- caught by type-system
    // if(integer == nullptr){}

    PointerParam(0);
    PointerParam(NULL);
    PointerParam(nullptr);

    IntegerParam(0);
    // IntegerParam(NULL); -- Some compiler *may* allow with warning -- even worse!
    //IntegerParam(nullptr); -- Error!

    return 0;
}
