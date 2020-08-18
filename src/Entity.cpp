#include "Entity.hpp"
#include "Component.hpp"

Entity::Entity(std::string name) { m_name = name; }
bool Entity::contains_signature (ComponentListSignature signature) const {
    return (m_signature & signature) == signature;
}

bool Entity::is_still_alive(){ return m_is_alive; }


Component& Entity::get_component(ComponentID component_id){
    return *m_pComponents[component_id];
}
bool Entity::has_component(ComponentID component_id) const {
    return m_signature & Component::get_component_signature(component_id);
}
void Entity::add_component(std::unique_ptr<Component> component){
    this->m_signature |= Component::get_component_signature(component->m_componentID);

    m_pComponents.emplace(
        component->m_componentID,
        std::move(component)
    );
}

