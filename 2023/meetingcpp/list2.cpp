// list2.cpp
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

    // Splice example
    std::list<int> list3{15,25,35,45};
    auto list3_iter = list3.begin();
    std::advance(list3_iter,2);

    myList.splice(end(myList),
                    list3,
                    list3_iter,
                    end(list3));

    printList(myList);
    printList(list3);

    return 0;
}









