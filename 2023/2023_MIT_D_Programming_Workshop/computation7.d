// @computation7.d
import std.stdio;
import std.algorithm;

void main()
{
    auto data = [1,2,4,7,4,7,8,6];
    // Check if our data is sorted
    writeln("isSorted : ", isSorted(data));
    // Partition our data around a value
    // Everything that satisifes a>4 is on the 'right'
    auto right = partition!"a>4"(data);
    writeln("right    : ", right);
    writeln("left     : ", data[0 .. right.length]);
    writeln("data     : ", data);
    // Sort our data
    writeln("sorted   : ", data.sort);
}


