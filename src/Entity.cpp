#include "Entity.hpp"


void Entity::add_component(std::unique_ptr<Component> component){

    this->m_signature |= Component::get_component_signature(component->m_componentID);

    m_pComponents.emplace(
        component->m_componentID,
        std::move(component)
    );
}
