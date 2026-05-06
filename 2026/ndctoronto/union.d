// @file: union.d 
import std.stdio;

void main(){

  union Value{
    int i;
    char c;
  };

  Value value;
  value.i=78;

  value.i.writeln; // Equivalent to 'writeln(value.i)'
  value.c.writeln; // Equivalent to 'writeln(value.c)'

}
