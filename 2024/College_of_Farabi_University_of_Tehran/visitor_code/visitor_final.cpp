/// @file: visitor_final.cpp
/// g++ -std=c++20 visitor_final.cpp -o prog && ./prog
#include <iostream>
#include <vector>

// Forward Declarations
// of all of the Monsters that are going to exist.
struct Orc;
struct Goblin;

/// The 'MonsterVisitor' will represent how we 'extend' each of
/// the 'Orc', 'Goblin', etc. with more functionality.
/// This 'visitor class' serves as a base class for other functionality
/// that we will add.
struct MonsterVisitor{
    virtual ~MonsterVisitor() = default;

    // Per 'Monster' I need a 'visit' function that
    // takes in the type of an object in the 'Monster hierarchy'
    // (i.e. must be 'typeof' Monster)
    virtual void visit(const& Orc)      const =0;
    virtual void visit(const& Goblin)   const =0;
};

/// Monster base class (for which Orc and Goblin will derive from)
/// Observe that we take in a 'MonsterVisitor' -- we 'accept' that
/// type.
struct Monster{
    /// Note this is implemented as a pure virtual function, because
    /// every type of Monster needs to implement this.
    virtual void accept(const MonsterVisitor&) = 0;
};

/// Orc 
struct Orc : public Monster{
    Orc(){
        std::cout << "Created a new Orc::Orc()\n";
    }

    /// We 'accept' the 'MonsterVisitor' base class
    void accept(const MonsterVisitor& visitor) override{
        std::cout << "Orc::accept\n";
        visitor.visit(*this);
    }
};

/// Goblin
struct Goblin : public Monster{
    Goblin(){
        std::cout << "Created a new Goblin::Goblin()\n";
    }

    /// We 'accept' the 'MonsterVisitor' base class
    void accept(const MonsterVisitor& visitor) override{
        std::cout << "Goblin::accept\n";
        visitor.visit(*this);
    }
};


// NOTE: For the visitor, could have this templated
//       to generate the implementations at compile-time that
//       are otherwise needed.
struct DrawMonsterVisitor : public MonsterVisitor{
    void visit(const Orc& orc) const override{
        std::cout << "\tDrawMonsterVisitor::visit(orc)\n";
    };
    void visit(const Goblin&  goblin) const override{
        std::cout << "\tDrawMonsterVisitor::visit(goblin)\n";
    };
};

struct FightMonsterVisitor: public MonsterVisitor{
    void visit(const Orc& orc) const override{
        std::cout << "\tFightMonsterVisitor::visit(orc)\n";
    };
    void visit(const Goblin&  goblin) const override{
        std::cout << "\tFightMonsterVisitor::visit(goblin)\n";
    };
};


/// Function that is called to draw all the 'Monsters' in a collection
/// with the correct visitor.
/// We are iterating through each monster and simply 'dispatching' the
/// behavior for the monster based on the 'visitor type'
void drawAllMonsters(std::vector<Monster*> const& monsters){
    for(auto const& m : monsters){
        m->accept(DrawMonsterVisitor{});
    }
}

void fightAllMonsters(std::vector<Monster*> const& monsters){
    for(auto const& m : monsters){
        m->accept(FightMonsterVisitor{});
    }
}

int main(){

    // Create a bunch of monsters
    std::vector<Monster*> monsters;
    monsters.emplace_back(new Orc);
    monsters.emplace_back(new Goblin);

    std::cout << std::endl;
    drawAllMonsters(monsters);

    std::cout << std::endl;
    fightAllMonsters(monsters);

    // Create a single Monster and enact some behavior
    std::cout << std::endl;
    std::cout << std::endl;

    Monster* myGoblin = new Goblin;
    FightMonsterVisitor fmv;
    myGoblin->accept(fmv);


    std::cout << std::endl;

    return 0;
}
