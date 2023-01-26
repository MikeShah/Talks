// @computation6.d
import std.stdio;
import std.algorithm; // sum function

void main()
{
    auto data = [1,2,4,7,4,7,8,6];
    // Test if all values satisfy condition
    writeln("all         : ", all!("a > 0")(data));
    // Test if any values satisfy condition
    writeln("any         : ", any!("a < 0")(data));
    // Find the smallest value
    writeln("minElement  : ",minElement(data)); 
    // Find index of smallest value
    writeln("minIndex    : ", minIndex(data));
}


