#include "TeamSystem.hpp"
#include "Game.hpp"

#include "Component.hpp"
#include "TransformComponent.hpp"
#include "TeamComponent.hpp"

TeamSystem::TeamSystem(Game &game)
    :   System(game, std::string("Team System"))
{
    m_signature |= Component::get_component_signature<TransformComponent>();
    m_signature |= Component::get_component_signature<TeamComponent>();
}

void TeamSystem::update(double dT){
    for(auto const entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){


        }
    }
}