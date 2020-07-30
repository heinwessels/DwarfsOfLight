#pragma once

#include <limits>

#include "Entity.h"
#include "Types.h"

// TODO Need some way for every new component to have a unique ID. Would be cool to happen at compile time

// template<typename T>
class Component{

    ComponentID m_component_id;     // What is my component Type ID
    EntityID m_entity_id;           // Know to which entity it belongs

    unsigned int m_pool_index;      // Know index of itself in vector of this type of component
    constexpr static unsigned int INVALID_POOL_INDEX = std::numeric_limits<int>::max();


public:
    Component() : m_entity_id (INVALID_ENTITY_ID), m_pool_index(INVALID_POOL_INDEX) { }

    virtual void init();

    void set_entity_id(EntityID entity_id) {m_entity_id = entity_id;}   // TODO: Should be private? Or friend?
    EntityID get_entity_id() {return m_entity_id;}
    void set_pool_index(int pool_index) {m_pool_index = pool_index;}
    unsigned int get_pool_index() {return m_pool_index;}

};