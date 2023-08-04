// @file ll.cpp
// Linked list example
// g++ -Wall -Wextra -std=c++17 ll.cpp -o prog
#include <iostream>

struct Node{
    Node(){
        data =0;
        next = nullptr;
    }
    int data;
    Node* next;
};

class SinglyLinkedList{
    public:
        SinglyLinkedList() { 
            m_head = nullptr; 
        }

        void PrependNode(int data){
             if(m_head==nullptr){
                m_head = new Node;
                m_head->data = data;
                m_head->next = nullptr;
             }else{
                Node* newNode = new Node;
                newNode->data = data;
                newNode->next = m_head;
                m_head = newNode;
             }
        }
        void PrintList(){
            Node* iter = m_head;
            while(iter!=nullptr){
                std::cout << iter->data << "\n";
                iter=iter->next;
            }
            std::cout << std::endl;
        }

        ~SinglyLinkedList(){
            Node* iter = m_head;
            Node* next = m_head->next;
            while(iter!=nullptr){
                delete iter;
                iter = next;
                if(iter!=nullptr){
                    next = iter->next;
                }
            }
        }
        // Copy constructor/Copy assignment operator
        // removed for breviety...
    private:
        Node* m_head;
};

int main(){
    
    SinglyLinkedList myList;

    myList.PrependNode(1);
    myList.PrependNode(2);
    myList.PrependNode(3);
    myList.PrependNode(4);
 
    myList.PrintList();
    // Free nodes...or handle in destructor

    return 0;
}
