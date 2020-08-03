#pragma once

#include <unordered_map>
#include <memory>

#include "Types.hpp"
#include "Component.hpp"

class Entity{

    ComponentListSignature m_signature = 0;

    // Storing component pointers in a hashmap. This will put them everywhere in memory.
    // Bad for caching.
    std::unordered_map<ComponentID, std::unique_ptr<Component>> m_pComponents;

public:
    bool has_signature (ComponentListSignature signature) const {return signature == m_signature;}  // TODO! Currently only true if exact match!
    Component& get_component(ComponentID component_id){return *m_pComponents[component_id];}

protected:
    void add_component(std::unique_ptr<Component> component);
};