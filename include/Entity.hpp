#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "Vec2.hpp"
#include "Types.hpp"

class Component;
class Entity{

    bool m_is_alive = true; // To trigger deletion by game
    ComponentListSignature m_signature = 0;

    // Storing component pointers in a hashmap. This will put them everywhere in memory.
    // Bad for caching.
    std::unordered_map<ComponentID, std::unique_ptr<Component>> m_pComponents;

    std::string m_name;     // This is only for debugging purposes

public:
    Entity(std::string name);
    bool contains_signature (ComponentListSignature signature) const;
    Component& get_component(ComponentID component_id);
    bool has_component(ComponentID component_id) const;

    bool is_still_alive();

protected:
    void add_component(std::unique_ptr<Component> component);
};