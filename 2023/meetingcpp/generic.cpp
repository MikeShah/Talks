// generic
#include <vector>
#include <array>

struct UDT{};

int main(){
    
    // standard vector container is 'generic'
    std::vector<int> v1;
    std::vector<UDT> v2;

    // Class Template Argument Deduction (CTAD)
    // Can automatically infer template arguments.
    //
    // NOTE: I recommend providing arguments regardless
    std::vector      v3 = {1L,2L,3L};

    return 0;
}
