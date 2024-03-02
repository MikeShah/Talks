// context.cpp
#include <algorithm>
#include <iostream>
#include <memory>

struct ICombat{
    ~ICombat(){}
    virtual void Execute(/* container, params */)=0;
};

struct NoCombat: public ICombat{
    void Execute(/* params */) override{
        std::cout << "Run away in fear!!\n";
    }
};
struct MeleeCombat : public ICombat{
    void Execute(/* params */) override{
        std::cout << "MeleeCombat::Execute(...)\n";
    }
};
struct RangedCombat : public ICombat{
    void Execute(/* params */) override{
        std::cout << "RangedCombat::Execute(...)\n";
    }
};

struct Orc /* The Context */ {

    std::unique_ptr<ICombat> mCombatStrategy;
    
    Orc(){
        mCombatStrategy = std::make_unique<NoCombat>();
    }

    void SetStrategy(std::unique_ptr<ICombat>&& combat){
        mCombatStrategy = std::move(combat);
    }

    void DoActions(){
        mCombatStrategy->Execute();
    }
};

int main(){

    Orc orc;

    orc.DoActions();

    /* time passes */
    orc.SetStrategy(std::make_unique<RangedCombat>());

    orc.DoActions();

    return 0;
}
