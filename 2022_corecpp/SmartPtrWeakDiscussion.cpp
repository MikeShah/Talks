// SmartPtrWeakDiscussion.cpp 
#include <iostream>
template <typename T>
class SmartPtr{
    public:
    SmartPtr() : m_data(new T), m_size(1){
		*m_data = 42;
	}
	// Handle allocations greater than 1
    SmartPtr(size_t size) : m_data(new T[size]),m_size(size){}
	
    ~SmartPtr(){
		destroy();
    }

	SmartPtr<T>& operator=(const SmartPtr<T>& rhs){		
		if(this==&rhs){
			return *this;
		}
		// destroy memory
		destroy();	
		// Assign pointee to rhs
		m_data = rhs.m_data;		m_size = rhs.m_size;


		return *this;
	}	

	// SmartPtrWeakDiscussion.cpp 
	// Dereference our smart pointer
	T& operator*() const{
		if(nullptr == m_data){
			// Handle
		}
		if(controlblock.refcount ==0){
			// Do something different
		}
		return *m_data;
	}

    private:
	void destroy(){
		if(m_data!=nullptr && m_refcount ==0){
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
	size_t m_refcount;
};

// SmartPtrSharedUse.cpp 
int main(){
   	{
        SmartPtr<int> s;
        SmartPtr<int> s1;
        SmartPtr<int> s2;

		std::cout << "s is" << (*s) << std::endl;

		// Only 1 owner at the end of this
		// No more double-free issue
		s = std::move(s2);
		s1 = std::move(s2);
	}    
    return 0;
}


