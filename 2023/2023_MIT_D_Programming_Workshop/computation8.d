// @computation8.d
import std.stdio;
import std.algorithm;
import std.range;

void main()
{
    auto data = [1,2,4,7,4,7,8,6];
    // Filter our data to meet some condition (a > 3)
    writeln(data.filter!(a=>a>3));
    // Operate on each element (multiply by 2)
    writeln(data.map!(a=>a * 2));
    // Reduce operation
    // HEY -- this is like our sum function!
    writeln(data.reduce!((a,b)=>a+b));
}
