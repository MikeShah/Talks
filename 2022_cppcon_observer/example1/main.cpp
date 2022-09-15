// example1/main.cpp
#include <string>
#include <iostream>
#include <forward_list>

// example1/main.cpp
// Abstract class, the idea is we will inherit from
// this class 
class IObserver{
	public: 
		virtual ~IObserver() {}
		virtual void OnNotify()=0;
};

// Watcher is derived from IObserver
class Watcher : public IObserver{
	public:
		explicit Watcher(const std::string& name) : mName(name){
		}

		void OnNotify(){
			std::cout << mName << "-hello!" << std::endl;
		}
	private:
		std::string mName;
};

// example1/main.cpp
// Now we have converted 'Subject' to 'ISubject'
// 'ISubject' now works with our IObserver interface
class ISubject{
	public:
		ISubject() {};
		virtual ~ISubject() {}

		virtual void AddObserver(IObserver* observer){
			mObservers.push_front(observer);
		}

		virtual void RemoveObserver(IObserver* observer){
			mObservers.remove(observer);
		}

		virtual void Notify(){
			for(auto& o: mObservers){
				o->OnNotify();
			}
		}

	private:
		std::forward_list<IObserver*> mObservers;
};

// example1/main.cpp
class SomeSubject : public ISubject{
		public:

};

// example1/main.cpp
int main(){

	SomeSubject subject;
	Watcher watcher1("watcher1");
	Watcher watcher2("watcher2");
	Watcher watcher3("watcher3");

	subject.AddObserver(&watcher1);
	subject.AddObserver(&watcher2);
	subject.AddObserver(&watcher3);
	
	subject.Notify();

	std::cout << std::endl;
	subject.RemoveObserver(&watcher1);

	subject.Notify();

	return 0;
}

