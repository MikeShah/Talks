// @file: rgb.d
import std.stdio;

void main(){

  int color1 =   17;         // Represent the number as 17
  int color2 = 0x11;         // Represent the number with hexadecimal.
  int color3 = 0b00000000_00000000_00000000_00010001; // Binary
  int color4 = 0x00_00_00_11; // hexadecimal, but 'readable'

  /// Write out the results
  color1.writeln;
  color2.writeln;
  color3.writeln;
  color4.writeln;

  // Unpack components of color4
  ubyte r = cast(ubyte)(color4 >> 24); // Shift 24-bits
  ubyte g = cast(ubyte)(color4 >> 16); // Shift 16-bits
  ubyte b = cast(ubyte)(color4 >> 8);  // Shift 8-bits
  ubyte a = cast(ubyte)(color4);       // Shift 0-bits (truncate)

  r.writeln;
  g.writeln;
  b.writeln;
  a.writeln;

}
