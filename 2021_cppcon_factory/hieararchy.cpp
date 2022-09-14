// @file hierarchy.cpp
// g++ -std=c++17 hierarchy.cpp
#include <vector>

class IGameObject{
    public:
        // Ensure derived classes call
        // the correct destructor (i.e., top of the chain)
        virtual ~IGameObject() {}
        // Pure virtual functions that must be
        // implemented by derived class
        virtual void ObjectPlayDefaultAnimation() = 0;
        virtual void ObjectMoveInGame() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
};

class Plane : public IGameObject{
    public:
    Plane(int x,int y){ /* ... */ }
    void ObjectPlayDefaultAnimation() { /* ... */}
    void ObjectMoveInGame() { /* ... */}
    void Update() { /* ... */}
    void Render() { /* ... */}
};

class Boat: public IGameObject{
    public:
    Boat(int x,int y){ /* ... */ }
    void ObjectPlayDefaultAnimation() { /* ... */}
    void ObjectMoveInGame() { /* ... */}
    void Update() { /* ... */}
    void Render() { /* ... */}
};


// Enum class so we will create a type
enum class ObjectType{PLANE, BOAT};

// One single function to create our object types
// The object will just 'do the right thing'
IGameObject* CreateObjectFactory(ObjectType o){
    switch(o){
        case ObjectType::PLANE:
            return new Plane(0,0);
        case ObjectType::BOAT:
            return new Boat(0,0);
    }
}


int main(){
    
    // Open some file
    std::vector<IGameObject*> gameObjectCollection; // Formerly our units1 and units2
    gameObjectCollection.push_back(CreateObjectFactory(ObjectType::PLANE));

    // ...
    while(true){
        // Run your game here

        // Iterate through your units
        // update them, run logic, etc.
    }

    return 0;
}
