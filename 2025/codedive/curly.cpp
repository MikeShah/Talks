#include <iostream>
#include <initializer_list>

struct UDT{
    UDT(int a, int b, int c){
        std::cout << "constructor with 3 params\n";
    }
    UDT(std::initializer_list<int> data) : m_data(data){
        std::cout << "initializer_list constructor\n";
    }

    ~UDT(){
    }
    void PrintData(){
        for(auto& e : m_data){
            std::cout << e << ", ";
        }
        std::cout << std::endl;
    }

    private:
    std::initializer_list<int> m_data;
};

int main(){

	

    // UDT u{1.0f,2.0f,3.0f}; // Will not work, 'narrowing conversion'
							  // May also be caught with: -Wnarrowing	
    UDT u{1,2,3};			  // Correct type


	UDT u2{1,2,3,4,5,6};      // List initializer constructor called

    u.PrintData();

    return 0;
}
