// @file: component.d
import std.stdio;

interface IComponent{}

class HealthComponent : IComponent { int value; }
class PowerComponent : IComponent { int value; }
class MagicComponent : IComponent { int value; }

struct GameEntity{
  string EntityName;
  
  // Dynamically populate 'components'
  IComponent[] mComponents;
}

void main(){
  GameEntity g = GameEntity("Mike");  // structs with no constructor are 
                                      // 'struct literals' which give us the
                                      // automatic constructor feel in D.
  g.mComponents ~= new HealthComponent;
  g.mComponents ~= new PowerComponent;
  g.mComponents ~= new MagicComponent;

  writeln(g.mComponents);
}
