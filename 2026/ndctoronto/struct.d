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

  // Casting type to a 'ubyte' and accessing field offsets.
  ubyte* color4 = cast(ubyte*)&c;
  color4[0].writeln;
  color4[1].writeln;
  color4[2].writeln;
  color4[3].writeln;

  return 0;
}
