#ifndef GAMEOBJECTS_HPP
#define GAMEOBJECTS_HPP

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

// @directory ./tracking
// GameObjects.hpp
class Plane : public IGameObject{
    public:
    Plane(int x,int y){ 
        ObjectsCreated++;
    }
    void ObjectPlayDefaultAnimation() { /* ... */}
    void ObjectMoveInGame() { /* ... */}
    void Update() { /* ... */}
    void Render() { /* ... */}
    static IGameObject* Create() {
        return new Plane(0,0);
    }
    private:
        static int ObjectsCreated;
};


class Boat: public IGameObject{
    public:
    Boat(int x,int y){ /* ... */ }
    void ObjectPlayDefaultAnimation() { /* ... */}
    void ObjectMoveInGame() { /* ... */}
    void Update() { /* ... */}
    void Render() { /* ... */}
    static IGameObject* Create() {
        return new Boat(0,0);
    }
    private:
        static int ObjectsCreated;
};

#endif
