// @file thread10.cpp
// g++ -std=c++17 thread10.cpp -o prog -lpthread
#include <iostream>
#include <future>

int square(int x){
    return x*x;
}

int main() {

    // asyncFunction is a 'future'
    // type = std::future<int>
    auto asyncFunction = std::async(&square,12);
    // .... some time passes
    int result = asyncFunction.get(); // We are blocked here if
                                      // our value has not been
                                      // computed. Otherwise, the
                                      // value from get() (which
                                      // is wrapped in a promise
                                      // is returned.
    std::cout << "The async thread has returned! " << result
              << std:: endl;

    return 0;
}



