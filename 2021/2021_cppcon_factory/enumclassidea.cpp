// @file enumclassidea.cpp
// g++ -std=c++17 enumclassidea.cpp
#include <vector>
#include <memory>

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
enum class ObjectType{PLANE,PLANE_IN_AIR, BOAT};

// One single function to create our object types
// The object will just 'do the right thing'
std::shared_ptr<IGameObject> CreateObjectFactory(ObjectType o){
    switch(o){
        case ObjectType::PLANE:
            return std::make_shared<Plane>(0,0);
        case ObjectType::PLANE_IN_AIR:
            return std::make_shared<Plane>(0,100000); // (x,y)
        case ObjectType::BOAT:
            return std::make_shared<Boat>(0,0);
    }
}


int main(){
    // Formerly our units1 and units2
    std::vector<std::shared_ptr<IGameObject>> gameObjectCollection; 
    // Add the correct object to our collection
    gameObjectCollection.push_back(CreateObjectFactory(ObjectType::PLANE));
    gameObjectCollection.push_back(CreateObjectFactory(ObjectType::PLANE));
    gameObjectCollection.push_back(CreateObjectFactory(ObjectType::PLANE));
    gameObjectCollection.push_back(CreateObjectFactory(ObjectType::BOAT));
    gameObjectCollection.push_back(CreateObjectFactory(ObjectType::BOAT));

    // Main Game Loop
    while(true){
        // Iterate through your game object
        // update them, run logic, etc.
        for(auto& e: gameObjectCollection){
            e->Update();
            e->Render();
        } 
    }

    return 0;
}


