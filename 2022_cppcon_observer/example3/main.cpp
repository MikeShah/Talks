// example3/main.cpp
#include <string>
#include <iostream>
#include <forward_list>
#include <map>          // New data structure
#include <memory> 		// shared_ptr

// Different types of messages
enum class MessageTypes{PLAYSOUND, HANDLEPHYSICS, LOG};	

// example3/main.cpp
// Abstract class, the idea is we will inherit from
// this class 
class IObserver{
	public: 
		virtual ~IObserver() {}
		virtual void OnNotify()=0;
		// Retrieve the 'Watcher' name
		virtual std::string GetName() const= 0 ;
};

// SoundEvent is derived from IObserver
class SoundEvent : public IObserver{
	public:
		explicit SoundEvent(const std::string& name) : mName(name){
		}
		// Do something 'physics like'
		void OnNotify() override{
			std::cout << mName << " Sound engine did something" << std::endl;
		}

		std::string GetName() const override { return mName; }
	private:
		std::string mName;
};
// PhysicsEvent is derived from IObserver
class PhysicsEvent : public IObserver{
	public:
		explicit PhysicsEvent(const std::string& name) : mName(name){
		}
		// Do something 'physics like'
		void OnNotify() override{
			std::cout << mName << " physics engine did something" << std::endl;
		}

		std::string GetName() const override { return mName; }
	private:
		std::string mName;
};
// LogEvent is derived from IObserver
class LogEvent : public IObserver{
	public:
		explicit LogEvent(const std::string& name) : mName(name){
		}
		// Do something 'physics like'
		void OnNotify() override{
			std::cout << mName << " log did something" << std::endl;
		}

		std::string GetName() const override { return mName; }
	private:
		std::string mName;
};

// example3/main.cpp
// Our 'subject' will now be able to handle different
// types of 'messages/events/keys' that happen.
// This opens our subject up to working with different 
// subsystems, but still staying decoupled.
class ISubject{
	public:
		ISubject() {};
		virtual ~ISubject() {}

		// Message is the 'key' or 'event' that we want to handle.
		// 'observer' is the observer we'll add to the events
		virtual void AddObserver(MessageTypes message, std::shared_ptr<IObserver>& observer){
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

		virtual void RemoveObserver(MessageTypes message, std::shared_ptr<IObserver>& observer){
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

		// example3/main.cpp
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
		virtual void Notify(MessageTypes message){
			for(auto& o: mObservers[message]){
				o->OnNotify();
			}
		}

	private:
		// Two typedefs here, one for the list of observers (same as before)
		typedef std::forward_list<std::shared_ptr<IObserver>> 	ObserversList;
		// The map is going to store 'int' as the key.
		// The key is for each of the 'messages'
		// Then, the value in our map is a forward_list as previous
		typedef std::map<MessageTypes, ObserversList> 		ObserversMap;
		ObserversMap mObservers;
};

// example3/main.cpp
class SomeSubject : public ISubject{
	public:
		MessageTypes message;
 };

// example3/main.cpp
int main(){

	SomeSubject subject;
	// Each of our 'watchers' are derived from IObserver.
	// They are each event types that can 'subscribe' to 
	// a subject, and when they're notified, do something 
	// specific to that subsystem, without being coupled.
	std::shared_ptr<IObserver> watcher1 = std::make_shared<SoundEvent>("watcher1");
	std::shared_ptr<IObserver> watcher2 = std::make_shared<PhysicsEvent>("watcher2");
	std::shared_ptr<IObserver> watcher3 = std::make_shared<LogEvent>("watcher3");

	subject.AddObserver(MessageTypes::PLAYSOUND, 	 watcher1);
	subject.AddObserver(MessageTypes::HANDLEPHYSICS, watcher2);
	subject.AddObserver(MessageTypes::LOG, 			 watcher3);
	

	// Send messages to every observer for this subject, regardless
	// of the 'MessageTypes'
	subject.NotifyAll();

	// Notify any observer that has to do with 'sound'
	subject.Notify(MessageTypes::PLAYSOUND);
	std::cout << std::endl;
	subject.RemoveObserver(MessageTypes::PLAYSOUND, watcher1);

	// Notice, no messages sent now
	subject.Notify(MessageTypes::PLAYSOUND);

	return 0;
}

