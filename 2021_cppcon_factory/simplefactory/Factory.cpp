#include "Factory.hpp"

#include "GameObjects.hpp"

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




