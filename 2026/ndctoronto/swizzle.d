// @file: swizzle.d
import std.stdio;

int main(){

  int color4 = 0x01_02_03_04; // hexadecimal, but 'readable'
  // Unpack components of color4 so you can see original order
  ubyte r = cast(ubyte)(color4 >> 24); // Shift 24-bits
  ubyte g = cast(ubyte)(color4 >> 16); // Shift 16-bits
  ubyte b = cast(ubyte)(color4 >> 8);  // Shift 8-bits
  ubyte a = cast(ubyte)(color4);       // Shift 0-bits (truncate)

  writeln(i"original result -- r: $(r) g: $(g) b:$(b) a:$(a)");

  // Perform the swizzle in one operation.
  //
  // - 1st expression is selecting the byte with a 'mask' 
  //   - (e.g. 0xFF_00_00_00) selects leading byte
  // - Then we 'shift' our 'byte' left or right by number of bits
  //   - (Make sure to do this in increments of '8' to match byte size.
  // - Finally we 'or' all of the results together.
  color4 =  ((color4 & 0xFF_00_00_00) >> 24)  | 
            ((color4 & 0x00_FF_00_00) >> 8)   |
            ((color4 & 0x00_00_FF_00) << 8)   |
            ((color4 & 0x00_00_00_FF) << 24);

  r = cast(ubyte)(color4 >> 24); // Shift 24-bits
  g = cast(ubyte)(color4 >> 16); // Shift 16-bits
  b = cast(ubyte)(color4 >> 8);  // Shift 8-bits
  a = cast(ubyte)(color4);       // Shift 0-bits (truncate)
  writeln(i"reversed result -- r: $(r) g: $(g) b:$(b) a:$(a)");


  return 0;
}
