#include "MovementSystem.hpp"
#include "Game.hpp"

MovementSystem::MovementSystem(Game &game)
    :   System(game)
{
    m_signature |= Component::get_component_signature(MoveComponentID);
}

void MovementSystem::update(float dT){
    for(auto const entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){

            MoveComponent &move = static_cast<MoveComponent&>(entity->get_component(MoveComponentID));

            entity->set_posision(entity->get_posision() + move.speed * dT);
        }
    }
}