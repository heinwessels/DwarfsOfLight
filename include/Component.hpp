#pragma once

#include "Types.hpp"

class Component{
public:
    const ComponentID m_componentID;
    Component(ComponentID componentID) : m_componentID(componentID) { }
    static ComponentListSignature get_component_signature(ComponentID component_id){return 1<<component_id;}
};