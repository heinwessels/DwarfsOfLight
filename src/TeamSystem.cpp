#include "TeamSystem.hpp"
#include "Game.hpp"

#include <limits>

#include "Entity.hpp"
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
            handle_entity(*entity);
        }
    }
}

void TeamSystem::handle_entity(Entity &entity){

    auto &transform = entity.get_component<TransformComponent>();
    auto &team = entity.get_component<TeamComponent>();

    // Reset variables by default
    team.enemy_close = false;
    team.foe_close = false;

    if (!team.flees_from.size() && !team.attacks.size())
        return; // This entity does not care about other entities

    for(auto const stranger : m_pgame.get_entities()){
        // For every entity in the world

        if (&entity != stranger){
            // He is not a stranger to himself

            if (has_valid_signature(*stranger)){
                // He must also be part of a team

                auto &stranger_team = stranger->get_component<TeamComponent>();
                auto &stranger_transform = stranger->get_component<TransformComponent>();

                // For each enemy to flee from
                double closest_distance_square = std::numeric_limits<double>::max();
                for (auto const & enemy : team.flees_from){
                    if (stranger_team.team == enemy){

                        double distance_square = Vec2::dist_sq(transform.position, stranger_transform.position);
                        if (
                            distance_square < team.vision_radius*team.vision_radius &&
                            distance_square < closest_distance_square
                        ){
                            // We must fear this enemy
                            team.enemy_close = true;
                            team.enemy_close_dir = Vec2::norm(transform.position - stranger_transform.position);
                        }
                    }
                }

                // For each enemy we can attack
                closest_distance_square = std::numeric_limits<double>::max();
                for (auto const & enemy : team.attacks){
                    if (stranger_team.team == enemy){

                        double distance_square = Vec2::dist_sq(transform.position, stranger_transform.position);
                        if (
                            distance_square < team.vision_radius*team.vision_radius &&
                            distance_square < closest_distance_square
                        ){
                            // We must fear this enemy
                            team.foe_close = true;
                            team.foe_close_dir = Vec2::norm(transform.position - stranger_transform.position);
                        }
                    }
                }
            }
        }
    }
}