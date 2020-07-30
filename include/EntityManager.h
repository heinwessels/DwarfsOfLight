#pragma once

#include <vector>
#include <unordered_map>

#include "Entity.h"
#include "Component.h"
#include "System.h"


// This is the main manager of the ECS
class EntityManager{

    // All components of same type in a list, within a bigger list of different types

    // This is stored as a pointer to handle templates.
    // TODO overwrite <new> to do it some kind of memory pool
    using Components = std::vector<std::vector<Component*>>;

    // Hashmap. Easy to add/remove without moving memory.
    // And still fairly quickly to access.
    using Entities = std::unordered_map<EntityID, Entity>;

    using Systems = std::vector<System*>;


    void init();
    void update(float dT);      // This will loop through SYSTEMS and update each

    void create_systems(); // Temporary


    EntityID create_entity();   // This still need some info to be sent
    void destroy_entity(EntityID entity_id);

private:

    // Here we will STORE all components, systems, and the corresponding entities
    Components m_components;    // This is ALL components that exist everywhere
    Entities m_entities;
    Systems m_systems;

};