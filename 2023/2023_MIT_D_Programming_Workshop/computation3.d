// @computation3.d
import std.stdio;

auto sum(int[] input){
    int sum;
    foreach(element; input){
        sum += element;
    }
    return sum;
}

void main()
{
    auto data = [1,2,4,7,4,7,8,6];
    
    writeln(sum(data));
}


