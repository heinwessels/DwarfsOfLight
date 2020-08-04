#pragma once

#include <unordered_map>
#include <memory>

#include "Types.hpp"
#include "Component.hpp"

class Entity{

    bool m_is_alive = true; // To trigger deletion by game
    ComponentListSignature m_signature = 0;

    // Storing component pointers in a hashmap. This will put them everywhere in memory.
    // Bad for caching.
    std::unordered_map<ComponentID, std::unique_ptr<Component>> m_pComponents;

public:
    bool contains_signature (ComponentListSignature signature) const {return (m_signature & signature) == signature;}
    Component& get_component(ComponentID component_id){return *m_pComponents[component_id];}

    bool is_still_alive(){ return m_is_alive; }

protected:
    void add_component(std::unique_ptr<Component> component);
};