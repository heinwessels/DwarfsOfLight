#pragma once

#include <unordered_map>
#include <memory>

#include "Types.hpp"
#include "Component.hpp"

class Entity{

    EntitySignature m_signature = 0;

    // Storing component pointers in a hashmap. This will put them everywhere in memory.
    // Bad for caching.
    std::unordered_map<ComponentID, std::unique_ptr<Component>> m_pComponents;

public:
    bool has_signature(EntitySignature signature){return signature == m_signature;}

protected:
    void add_component(std::unique_ptr<Component> component);
};