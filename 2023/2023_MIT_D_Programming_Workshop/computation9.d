// @computation9.d
import std.stdio;
import std.algorithm;
import std.range;

void main()
{
    auto data = [1,2,4,7,4,7,8,6];
	// Map, reduce, and filter
    auto result = data.filter!("a > 6")
        				.map!(a=>a*2)
        				.fold!((a,b)=>a+b); 
    // Note: fold funtionality the same as reduce
    
    writeln("result: ", result);   
}


