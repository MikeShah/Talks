// Var.d
// Helpful post: 
// https://stackoverflow.com/questions/22084223/creating-a-certain-struct-at-run-time-in-c
//
// The purpose of this example is to show a very basic demonstration of how you
// can create your own 'var' dynamic type. In this case, you can point the data
// to any of the 'primitive types'.
//
// As an exercise using reflection, you could extend this to otherwise point to 'any' type that you have found statically as well as any type in a repository of the 'RunTimeStruct'.
//
// The second part of this example shows a 'RunTimeStruct' in which you can
// otherwise build a 'map' of fields.
//
// Note: This part could be further extend to otherwise list the types in order
//       with known offsets perhaps, or actually 'generate' code.
// 

// Demonstration of creating a 'Var' type
import std.stdio, std.conv;

mixin("int global;");


/*
enum header = "enum Type{";
enum body_  = "INT,STRING";
enum footer = "};";


/// Example showing that we can create data at compile-time anywhere.
static foreach(a ; [1,2,3]){
  mixin("int ddd"~a.to!string~";");
}
*/



/// The purpose of this is to create a 'struct' at run-time.
/// The idea is to use a 'map' of 'Var' so that you can add any type
/// as needed.
struct RunTimeStruct{
  Var[string] mFields;

  void AddField(Type type, string name){
    mFields[name] = Var(type,name);
  }

  string toString(){
      string result;
      foreach(k, v ; mFields){
        result ~= v.mType.to!string~"\t"~k~";\n";
      }
      return result;
  }
}

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

void main(){
  /// Demonstration of creating a 'var type';
  Var myVar = Var(Type.INT, "myInteger");

  myVar = 7;
  myVar.mData.i = 7; // Equivalent to above

  myVar = "Some string";
  myVar.mData.s = "Some string";
  //writeln(myVar.s);

  writeln(myVar);

  // Now let's create a struct at 'run-time' 
  // that includes the various fields that we need.
  RunTimeStruct myStruct;

  myStruct.AddField(Type.INT,"intField");
  myStruct.AddField(Type.STRING,"stringField");

  writeln(myStruct);
}
