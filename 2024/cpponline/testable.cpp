// testable.cpp
#include <algorithm>
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

void generic_sort(/*container, params*/){
    std::unique_ptr<ISorts> sorting_algo = std::make_unique<BubbleSort>();

    int collectionSize = 52;
    if(collectionSize< 16){
        sorting_algo = std::make_unique<BubbleSort>();
    }else if (collectionSize>= 16 && collectionSize < 64){
        sorting_algo = std::make_unique<InsertionSort>();
    }

    sorting_algo->Sort();
}

bool unittest1(){
    std::vector some_vector{1,3,6,4,2,5};

    std::unique_ptr<ISorts> sorting_algo = std::make_unique<BubbleSort>();
    sorting_algo->Sort();

    return std::is_sorted(some_vector.begin(),some_vector.end());
}

bool unittest2(){
    std::vector some_vector{1,3,6,4,2,5};

    std::unique_ptr<ISorts> sorting_algo = std::make_unique<InsertionSort>();
    sorting_algo->Sort();

    return std::is_sorted(some_vector.begin(),some_vector.end());
}

int main(){

    unittest1();
    unittest2();

    return 0;
}
