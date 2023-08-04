// g++ -g -Wall -std=c++20 lazy.cpp -o prog -lpthread
#include <iostream>
template<class T>
class Susp
{
    // thunk
    static T const & thunkForce(Susp * susp) {
        return susp->setMemo();
    }
    // thunk
    static T const & thunkGet(Susp * susp) {
        return susp->getMemo();
    }
    T const & getMemo() {
        return _memo;
    }
    T const & setMemo() {
        _memo = _f();
        _thunk = &thunkGet;
        return getMemo();
    }
public:
    explicit Susp(std::function<T()> f)
        : _f(f), _thunk(&thunkForce), _memo(T())
    {}
    T const & get() {
        return _thunk(this);
    }
private:
    T const & (*_thunk)(Susp *);
    mutable T   _memo;

    std::function<T()> _f;
};

// Entry point to program
int main(int argc, char* argv[]){



    return 0;
}



