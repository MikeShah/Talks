// isorts_modern.cpp
#include <iostream>
#include <memory>

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

    std::unique_ptr<ISorts> sorting_algo = std::make_unique<InsertionSort>();

    sorting_algo->Sort();

    return 0;
}
