// @file: functionpointers.d 
import std.stdio;
import std.functional;

struct GameEntity{
  string EntityName;
  int health;
  int power;

  this(string name, int h, int p){
    EntityName  = name;
    health      = h;
    power       = p;
  }

  // Unparamertized and 'very concrete' action.
  void Attack(){
    i"Doing $(this.power) damage".writeln;
  }

  // Parameterized attack
  void Attack(int type){
    switch(type){
      case 1:
        i"Doing $(this.power) damage".writeln;
        break;
      case 2:
        i"Doing special attack for $(this.power*2) damage".writeln;
        break;
      default:
        i"Attack failed".writeln;
        break;
    }
  }

  void Attack(void function(int) behavior, int param1){
    behavior(param1);
  }


  // Member functions / behaviors / actions
  // C-equivalent function pointer 'void (*action1)(int);'
  void function(ref GameEntity g, int) action1;
  // We can get rid of the 'this' pointer, well...we don't get rid of it,
  // but we hide it in a 'delegate' and then can make our interface cleaner.
  void delegate(int) doaction1;
};




GameEntity GameEntity_Constructor(string name, int h, int p){
  GameEntity g;
  g.EntityName = name;
  g.health = h;
  g.power  = p;

  // Setup the object 'action1'
  g.action1 = &Attack;
  // Make client interface easier by 'binding' first argument.
  g.doaction1 = &partial!(Attack,g);

  return g;
}

void Attack(ref GameEntity g, int boost){
  writeln(g.EntityName, " attack1!", g.power +boost);
}

void higher_order_function(int bonus){
  writeln("Changing the strategy and adding a bonus:",bonus);
}

int main(){

  GameEntity g1 = GameEntity_Constructor("Mike",5,10);

  g1.Attack();
  g1.Attack(1);
  g1.Attack(&higher_order_function,15);



  g1.Attack(2);
  g1.Attack(3);
  g1.action1(g1,4); // Explicit call on object, but slightly annoying
  g1.doaction1(5);  // 'Easier' client interface that does the same thing

  GameEntity g2 = GameEntity_Constructor("Michael",6,11);
  g2.doaction1(10);

  g1.doaction1(5);  // 'more' what we're use to

  return 0;
}
