// @file: variant.cpp
#include <print>
#include <variant> // C++ 17 and beyond

union U{
    int i;
    short s;
};

int main(){
    std::variant<int, float> d;
    std::println("(Union) 	U sizeof = {}", sizeof(U));
    std::println("(variant) d sizeof = {}", sizeof(d));
    d = 7.14f;

	// index of variant that is selected
    std::println("{}",d.index());

	// 'attempt' is a pointer to the data if we have that type available.
    if(auto attempt = std::get_if<float>(&d)){
        std::println("we can access as a float: {}",*attempt);
    }

    return 0;
}
