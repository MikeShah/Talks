// g++ -g -Wall -std=c++20 linkedlist.cpp -o prog
#include <iostream>

struct Node{
    Node* next;
    int data;
};

struct LL1{
    Node* mHead{nullptr};

    void Append(int _data){
        Node* newNode = new Node;
        newNode->data = _data;
        newNode->next = nullptr;

        if(nullptr == mHead){
            mHead = newNode; 
        }else{
            Node* iter = mHead;
            
            while(nullptr != iter->next){
                iter=iter->next;
            }
            iter->next = newNode;
        }
    }

    void Print(){
        Node* iter = mHead;
        while(nullptr != iter){
            std::cout << iter->data << "\n";
            iter=iter->next;
        }
    }
};

struct LL2{
    Node* mHead{nullptr};
    Node* mTail{nullptr};

    void Append(int _data){
        Node* newNode = new Node;
        newNode->data = _data;
        newNode->next = nullptr;

        if(nullptr == mHead){
            mHead = newNode; 
            mTail = mHead;
        }else{ 
            mTail->next = newNode;
            mTail = newNode;
        }
    }

    void Print(){
        Node* iter = mHead;
        while(nullptr != iter){
            std::cout << iter->data << "\n";
            iter=iter->next;
        }
    }
};

// Entry point to program
int main(int argc, char* argv[]){

    if(argc==3){
        
        const int size = std::stoi(argv[2]);
        std::cout << "experiment size:" << size << std::endl;
   
        if(std::stoi(argv[1])==1){
            LL1 list1;
            for(int i=0; i < size; ++i){
                list1.Append(i);
            }
            //list1.Print();
        }
        else if(std::stoi(argv[1])==2){
            LL2 list2;
            for(int i=0; i < size; ++i){
                list2.Append(i);
            }
            //list2.Print();
        }
    }else{
            std::cout << "./prog 1 1000 or ./prog 2 1000\n";
    }


}
