// @file: command.d
import std.stdio;
class GameEntity{
  string name;
}

interface ICommand{
  void execute();
}

class Attack : ICommand{
  GameEntity g;
  int damage;
  int target;
  override void execute(){ "attacking".writeln; }
}

class Move : ICommand{
  GameEntity g;
  int x,y;
  override void execute(){ "moving".writeln;    }
}

class Exit : ICommand {
  override void execute() { "Exiting".writeln;  } 
}

void main(){

  ICommand[] commandQueue;
  commandQueue ~= new Attack();
  commandQueue ~= new Attack();
  commandQueue ~= new Move();
  commandQueue ~= new Exit();
  commandQueue ~= new Move();

  while(   typeid(cast(Object)commandQueue[0]).name != 
					 typeid(Exit).name  )
  {
    if(commandQueue.length >0){
      // Execute first command on queue
      commandQueue[0].execute();
      // 'pop' command off queue
      commandQueue = commandQueue[1..$];
    }    
    writeln("Next command is:",typeid(cast(Object)commandQueue[0]).name);
  }

  writeln("End of Main");
}

