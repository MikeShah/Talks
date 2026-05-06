// @file: struct.d
import std.stdio;

struct color{
  ubyte r;
  ubyte g;
  ubyte b;
  ubyte a;
}

int main(){

  color c = color(0,0,0,17);

  c.writeln;

  return 0;
}
