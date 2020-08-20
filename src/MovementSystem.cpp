#include "MovementSystem.hpp"
#include "Game.hpp"

#include "Entity.hpp"
#include "TransformComponent.hpp"

MovementSystem::MovementSystem(Game &game)
    :   System(game, std::string("Moving System"))
{
    m_signature |= Component::get_component_signature<TransformComponent>();
}

void MovementSystem::update(double dT){
    for(auto const entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){

            TransformComponent &transform = entity->get_component<TransformComponent>();

            transform.position += transform.speed * dT;
        }
    }
}