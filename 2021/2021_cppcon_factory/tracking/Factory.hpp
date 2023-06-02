#ifndef FACTORY_HPP
#define FACTORY_HPP
// @directory /simplefactory
// g++ -std=c++17 main.cpp Factory.cpp
#include <memory>

// Declare our one interface type
class IGameObject;

// Enum class so we will create a type
// Could list it in the header here so clients
// know what types they can create
enum class ObjectType{PLANE,PLANE_IN_AIR, BOAT};

// One single function to create our object types
// The object will just 'do the right thing'
std::shared_ptr<IGameObject> CreateObjectFactory(ObjectType o);


#endif

