// @computation2.d
import std.stdio;

void main()
{
    auto data = [1,2,4,7,4,7,8,6];
    
    int sum;
    foreach(element; data){
        sum += element;
    }

    writeln(sum);
}

