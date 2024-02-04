// Compile: dmd compile_time_sort.d -of=prog
// Run    : ./prog

void main(){
    import std.algorithm, std.stdio;
    
    "Hello Fosdem 2024".writeln;

    enum a = [3,1,2,4,0];
    
    static immutable b = sort(a);

    pragma(msg, "Finished compilation: ", b);

}
