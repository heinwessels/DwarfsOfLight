#include "MovementSystem.hpp"
#include "Game.hpp"

MovementSystem::MovementSystem(Game &game)
    :   System(game, std::string("Moving System"))
{
    m_signature |= Component::get_component_signature(TransformComponentID);
}

void MovementSystem::update(double dT){
    for(auto const entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){

            TransformComponent &transform = static_cast<TransformComponent&>(entity->get_component(TransformComponentID));

            transform.position += transform.speed * dT;
        }
    }
}