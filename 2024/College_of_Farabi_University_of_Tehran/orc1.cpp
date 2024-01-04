// @file orc1.cpp
// g++ -std=c++20 orc1.cpp -o prog && ./prog
#include <iostream>
#include <string>

struct Position{
    float x,y,z;
};

struct Attributes{
    // Perhaps 'encapsulate' 'Motive'
    struct Motive{};

    int power;
    std::string name;
    int rank;
    Motive m;
    Position p;
};

class orc{
    public:
        orc(){}

    private:
        Attributes attr;
};

int main(){
    return 0;
}
