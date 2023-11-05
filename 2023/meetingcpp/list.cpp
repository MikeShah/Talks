// list.cpp
#include <iostream>
#include <list>

void printList(const std::list<int>& list){
    std::cout << "==============\n";
    for(const auto& e: list){
        std::cout << e << ",";
    }
    std::cout << std::endl;
}

int main(){

    std::list<int> myList;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);

    // O(1) if front or end, otherwise O(n)
    myList.insert(begin(myList),5);
    myList.insert(end(myList),0);

    auto it = cbegin(myList);
    std::advance(it,myList.size()/2);
    std::cout << "middle is: " << *it << std::endl;

    myList.sort();
    myList.reverse();
    
    // member function 'erases' elements for us
    myList.remove_if([](int n) {return n<2;});

    printList(myList);

    return 0;
}









