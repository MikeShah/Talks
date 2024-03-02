// isorts.cpp
#include <iostream>

struct ISorts{
    ~ISorts(){}

    virtual void Sort(/* container, params */)=0;
};

struct InsertionSort : public ISorts{
    void Sort(/* container, params */) override{
        std::cout << "InsertionSort::Sort\n";
    }
};

struct BubbleSort : public ISorts{
    void Sort(/* container, params */) override{
        std::cout << "BubbleSort::Sort\n";
    }
};

int main(){

    ISorts* sorting_algo = new InsertionSort;

    sorting_algo->Sort();

    delete sorting_algo;

    return 0;
}
