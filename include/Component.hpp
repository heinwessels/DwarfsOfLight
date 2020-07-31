#pragma once

#include "Types.hpp"

class Component{
public:
    const ComponentID m_componentID;
    Component(ComponentID componentID) : m_componentID(componentID) { }
};