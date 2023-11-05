// generic3.cpp
#include <vector>
#include <list>

// alias template
template<class T>
using MyType = std::list<T>;

struct UDT{};

int main(){
    
    // standard vector container is 'generic'
    MyType<int> v1;
    MyType<UDT> v2;

    // Class Template Argument Deduction (CTAD)
    // Can automatically infer template arguments.
    //
    // NOTE: I recommend providing arguments regardless
    MyType<long>      v3 = {1L,2L,3L};

    return 0;
}
