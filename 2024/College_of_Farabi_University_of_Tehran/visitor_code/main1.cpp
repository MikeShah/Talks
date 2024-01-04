/// @file: main1.cpp
/// g++ -std=c++20 main1.cpp -o prog && ./prog
#include <iostream>
#include <vector>

/// Monster base class (for which Orc and Goblin will derive from)
struct Monster{
    virtual void Sing() = 0;
};

/// Orc 
struct Orc : public Monster{
    Orc(){
        std::cout << "Created a new Orc::Orc()\n";
    }
    void Sing() {
        std::cout << "Orc::Sing()\n";
    }
};

/// Goblin
struct Goblin : public Monster{
    Goblin(){
        std::cout << "Created a new Goblin::Goblin()\n";
    }
    void Sing() {
        std::cout << "Orc::Sing()\n";
    }
};

int main(){
    // Create a bunch of monsters
    std::vector<Monster*> monsters;
    monsters.emplace_back(new Orc);
    monsters.emplace_back(new Goblin);

    for(const auto& m: monsters){
        m->Sing();
    }
    // delete vector omitted for space
    return 0;
}
