// @file: bytecode.d

import std.stdio;
enum Type{INT, STRING };

union Data{
  int i;
  string s;
}

struct Var{
  Type   mType;
  string mName;  // Variable name
  Data   mData;

  this(Type type, string name){
    mType = type;
    mName = name;
  } 

  void opAssign(T)(T value){
    // assign based on the type, and verify
    static if(is(T==int)){
      if(is(mType==TYPE.INT)){
        mData.i = value;
      }
    }

    static if(is(T==string)){
      if(is(mType==Type.STRING)){
        mData.s = value;
      } 
    }
  }
}

void attack(Var[] args){
  writeln("attack: ",args[0].mData.i);
}
void move(Var[] args){
  writeln("mov   : ",args[0].mData.i,",",args[1].mData.i);
}

struct Command{
  // 'type' is the signature of 'attack' function
  // I got lazy and used 'typeof'.
  typeof(&attack) func;   
  // payload is the 'parameters' we'll pass to 'func'
  Payload payload;

  // If arguments are 'pre-packaged', use this version.
  void execute(){
    func(payload.args);
  }

  // If arguments are 'streamed in' use this version.
  void execute(Payload p){
    func(p.args);
  }
}

struct Payload{
  // Number of arguments for the 'func'
  int argCount;
  // Store up to '8' arguments for the arguments
  Var[8] args;
}


void main(){
  Command[] ByteCodeMap;
  // Attack function is 'bytecode 0' and takes '1' argument
  ByteCodeMap ~= Command(&attack,Payload(1));
  // Move function is 'bytecode 1' and takes '2' arguments
  ByteCodeMap ~= Command(&move,Payload(2));

  // 'Test program' of machine instructions
  int[] machine_instructions = [0,7,1,5,6,0,3,1,7,5];

  while(machine_instructions.length >0){
    // Top instruction must always be a machine instruction corresponding with
    // the 'byte code' -- in this case, index into our 'ByteCodeMap'
    int instruction = machine_instructions[0];
    machine_instructions = machine_instructions[1..$]; // pop instruction    

    // Based on the 'command' start popping off arguments
    // and populate a 'payload' based on how many arguments a 'command' expects.
    Payload p = Payload(ByteCodeMap[instruction].payload.argCount);
    for(int i=0; i < ByteCodeMap[instruction].payload.argCount; i++){
      p.args[i].mData.i = machine_instructions[0];
      machine_instructions = machine_instructions[1..$]; // pop instruction    
    }

    // Now execute command
    ByteCodeMap[instruction].execute(p);
  }
}

