#include "Entity.hpp"


void Entity::add_component(std::unique_ptr<Component> component){

    m_signature += 1>>component->m_componentID;

    m_pComponents.emplace(
        component->m_componentID,
        std::move(component)
    );
}
