// @file orc.cpp
// g++ -std=c++20 orc.cpp -o prog && ./prog
#include <iostream>
#include <string>

struct Motive{};

struct Position{
    float x,y,z;
};

class orc{
    public:
        orc(){}

    private:
        int power;
        std::string name;
        int rank;
        Motive m;
        Position p;
};

int main(){
    return 0;
}
