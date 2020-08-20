#pragma once

#include "Types.hpp"

class Component{
public:
    const ComponentID m_componentID;
    Component(ComponentID componentID) : m_componentID(componentID) { }

    template <class CompType>
    static ComponentListSignature get_component_signature(){return 1<<CompType::ID;}
};