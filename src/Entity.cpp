#include "Entity.hpp"
// #include "Component.hpp"

Entity::Entity(std::string name) { m_name = name; }
bool Entity::contains_signature (ComponentListSignature signature) const {
    return (m_signature & signature) == signature;
}

bool Entity::is_still_alive(){ return m_is_alive; }

