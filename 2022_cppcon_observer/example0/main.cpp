// example0/main.cpp
#include <string>
#include <iostream>
#include <forward_list>

// example0/main.cpp
class Observer{
	public:
		Observer(std::string name) : mName(name){
		}

		void OnNotify(){
			std::cout << mName << "-hello!" << std::endl;
		}
	private:
		std::string mName;
};

// example0/main.cpp
class Subject{
	public:
		void AddObserver(Observer* observer){
			mObservers.push_front(observer);
		}

		void RemoveObserver(Observer* observer){
			mObservers.remove(observer);
		}

		void Notify(){
			for(auto& o: mObservers){
				o->OnNotify();
			}
		}

	private:
		std::forward_list<Observer*> mObservers;
};


// example0/main.cpp
int main(){

	Subject subject;
	Observer observer1("observer1");
	Observer observer2("observer2");
	Observer observer3("observer3");

	subject.AddObserver(&observer1);
	subject.AddObserver(&observer2);
	subject.AddObserver(&observer3);
	
	subject.Notify();

	std::cout << std::endl;
	subject.RemoveObserver(&observer1);

	subject.Notify();

	return 0;
}


