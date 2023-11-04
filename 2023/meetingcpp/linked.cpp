// linked.cpp
#include <iostream>

struct node{
    int data;
    node* next;
};

int main(){

    node n1;
    node n2;

    n1.data = 5;
    n2.data = 7;

    n1.next = &n2;
    n2.next = nullptr;

    // Print out
    node* iter = &n1;
    while(iter!=nullptr){
        std::cout << iter->data << std::endl;
        iter=iter->next;
    }

    return 0;
}
