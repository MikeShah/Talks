// @file: taggedunion.d
import std.stdio;

/// Types available for our 'tagged union'
enum Type {INT, CHAR};

// Example of a 'tagged union'
struct Value{
  Type t;     // Spend extra bytes 'setting' type 
  union {
    int i;
    char c;
  }
}

void main(){
  Value v;
  v.t = Type.INT; // Set the type
  InitValue(v);
  writeln(v.i);

  v.t = Type.CHAR; // Set the type
  InitValue(v);
  writeln(v.c);
}

void InitValue(ref Value v){
  switch(v.t){
    case Type.INT:
      v.i = 500;
      writeln("Loaded with integer data:",v.i);
      break;
    case Type.CHAR:
      v.c = 'a';
      writeln("Loaded with char data:", v.c);
      break;
    default:
      assert(false,"unknown type");
  }
}
