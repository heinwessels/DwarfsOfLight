#pragma once

#include <unordered_map>

#include "Types.h"
#include "ComponentBase.h"

class Entity{

    EntityID m_id;

    // Here the Entity will store a reference to its components
    std::unordered_map<int /*some component ID*/, ComponentBase*> m_components;

public:
    explicit Entity(EntityID id) : m_id(id) { }
    EntityID get_id() const {return m_id;}


    // Some "get_component" function to return specific component of this entity
    // This will use template shenanigans
    template <class CompType>
    CompType get_component() const { }
};