// example2/main.cpp
#include <string>
#include <iostream>
#include <forward_list>
#include <map>          // New data structure

// example2/main.cpp
// Abstract class, the idea is we will inherit from
// this class 
class IObserver{
	public: 
		virtual ~IObserver() {}
		virtual void OnNotify()=0;
		// Retrieve the 'Watcher' name
		virtual std::string GetName() const= 0 ;
};

// Watcher is derived from IObserver
class Watcher : public IObserver{
	public:
		explicit Watcher(const std::string& name) : mName(name){
		}

		void OnNotify(){
			std::cout << mName << "-hello!" << std::endl;
		}

		std::string GetName() const override { return mName; }
	private:
		std::string mName;
};

// example2/main.cpp
// Now we have converted 'Subject' to 'ISubject'
// 'ISubject' now works with our IObserver interface
class ISubject{
	public:
		ISubject() {};
		virtual ~ISubject() {}

		// Message is the 'key' or 'event' that we want to handle.
		// 'observer' is the observer we'll add to the events
		virtual void AddObserver(int message, IObserver* observer){
			// Check to see if our 'key' or 'event type' is in our map
			auto it = mObservers.find(message);
			if(it==mObservers.end()){
				// Since we did not find our message, we need
				// to construct a new list
				mObservers[message] = ObserversList();
			}
			// Add our observer to the appropriate 'bucket' of events.
			mObservers[message].push_front(observer);
		}

		virtual void RemoveObserver(int message, IObserver* observer){
			// Check to see if our 'key' or 'event type' is in our map
			auto it = mObservers.find(message);
			if(it != mObservers.end()){
				// Find the right bucket in our map to find
				ObserversList& list = mObservers[message];
				// Now search through the list to erase our observer 
				for(ObserversList::iterator li = list.begin();
					li != list.end();){
					// Remove item if we find it
					if((*li)==observer){
						std::cout << "Goodbye " << observer->GetName() << std::endl;
						list.remove(observer);	
					}else{
						++li;
					}
				}
			}
		}

		// New function to notify everything
		virtual void NotifyAll(){
			// Search through every message type (our keys)
			for(ObserversMap::iterator it = mObservers.begin(); it!=mObservers.end(); ++it){
				for(auto& o : mObservers[it->first]){
					o->OnNotify();
				}
			}
		}
		// Notify a specific set of observers
		virtual void Notify(int message){
			for(auto& o: mObservers[message]){
				o->OnNotify();
			}
		}

	private:
		// Two typedefs here, one for the list of observers (same as before)
		typedef std::forward_list<IObserver*> 	ObserversList;
		// The map is going to store 'int' as the key.
		// The key is for each of the 'messages'
		// Then, the value in our map is a forward_list as previous
		typedef std::map<int, ObserversList> 		ObserversMap;
		ObserversMap mObservers;
};

// example2/main.cpp
class SomeSubject : public ISubject{
	public:
		enum MessageTypes{PLAYSOUND, HANDLEPHYSICS, LOG};	
};

// example2/main.cpp
int main(){

	SomeSubject subject;
	Watcher watcher1("watcher1");
	Watcher watcher2("watcher2");
	Watcher watcher3("watcher3");

	subject.AddObserver(SomeSubject::PLAYSOUND, 	&watcher1);
	subject.AddObserver(SomeSubject::HANDLEPHYSICS, &watcher2);
	subject.AddObserver(SomeSubject::LOG, 			&watcher3);
	

	// Send messages to every observer for this subject, regardless
	// of the 'MessageTypes'
	subject.NotifyAll();

	// Notify any observer that has to do with 'sound'
	subject.Notify(SomeSubject::PLAYSOUND);
	std::cout << std::endl;
	subject.RemoveObserver(SomeSubject::PLAYSOUND, &watcher1);

	// Notice, no messages sent now
	subject.Notify(SomeSubject::PLAYSOUND);

	return 0;
}

