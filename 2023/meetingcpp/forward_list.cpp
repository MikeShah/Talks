// forward_list.cpp
#include <iostream>
#include <forward_list>

void printList(const std::forward_list<int>& list){
    std::cout << "======================\n";
    for(const auto& e: list){
        std::cout << e << ","; 
    }
    std::cout << std::endl << std::endl;

}

// forward_list.cpp
void push_back(std::forward_list<int>& list, int val){
    auto pos = begin(list);
    int distance = std::distance(begin(list),
                                 end(list));
    std::advance(pos,distance-1);
    list.insert_after(pos,val);
}

int main(){

    // singly linked list (slist)
    std::forward_list<int> myList{1,2,3,4};

    myList.push_front(0);
    // WARNING: You might just want to use a 
    //          std::list, but this is 
    //          practice, showing how to add operations.
    //          Would probably want to return an iterator
    //          to speed this up!
    push_back(myList,5);
    push_back(myList,6);
    printList(myList);

    std::forward_list<int> list2{-2,0,3,4,5};
    // merges two already sorted lists
    // list2 will become empty after this operation
    myList.merge(list2);

    printList(myList);
    printList(list2);

    return 0;
}

