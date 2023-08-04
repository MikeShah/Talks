// SmartPtrOperators1.cpp 
#include <iostream>
template <typename T>
class SmartPtr{
    public:
    SmartPtr() : m_data(new T), m_size(1){}
	// Handle allocations greater than 1
    SmartPtr(size_t size) : m_data(new T[size]),m_size(size){}

    ~SmartPtr(){
		destroy();
    }
	// Operators
	// Assignment operator
	SmartPtr<T>& operator=(SmartPtr<T> rhs){
		if(this==&rhs){
			return *this;
		}
		// destroy memory
		destroy();	
		// Assign pointee to rhs
		m_data = rhs.m_data;
		m_size = rhs.m_size;
		return *this;
	}

    private:
    
	void destroy(){
		if(m_data!=nullptr){
			if(m_size>1){
				delete[] m_data;
			}else{
				delete m_data;
			}
			m_size=0;
		}
	}
	
	T* m_data;
	size_t m_size;
};

// SmartPtrOperators1.cpp 
int main(){
   	{
        SmartPtr<int> s;
        SmartPtr<int> s1;
        SmartPtr<int> s2;

		// Everyone points to 's2'
		s = s2;
		s1 = s2;
	}    
    return 0;
}


