#include "TeamSystem.hpp"
#include "Game.hpp"
#include "World.hpp"

#include <limits>
#include <list>

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
    for(auto &entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){
            handle_entity(*entity);
        }
    }
}

void TeamSystem::handle_entity(Entity &entity){

    auto &transform = entity.get_component<TransformComponent>();
    auto &team = entity.get_component<TeamComponent>();

    // Reset variables by default
    team.enemy_flee_close = false;
    team.enemy_attack_close = false;

    if (!team.flees_from.size() && !team.attacks.size())
        return; // This entity does not care about other entities

    // Get closest entities
    std::list<Entity*> entities_in_range = m_pgame.get_world().get_occupancy_map().find_entities_in_range(
        m_pgame.get_world(), transform.position, Vec2(2*team.vision_radius, 2*team.vision_radius)
    );
    double distance_sq_closest_enemy_attack = std::numeric_limits<double>::max();
    double distance_sq_closest_enemy_flee = std::numeric_limits<double>::max();
    for(auto const &stranger : entities_in_range){
        // For every entity in the world

        if (&entity != stranger){
            // He is not a stranger to himself

            if (has_valid_signature(*stranger)){
                // He must also be part of a team

                auto &stranger_team = stranger->get_component<TeamComponent>();
                auto &stranger_transform = stranger->get_component<TransformComponent>();

                // For each enemy to flee from
                for (auto const & enemy : team.flees_from){
                    if (stranger_team.team == enemy){

                        double distance_square = Vec2::dist_sq(transform.position, stranger_transform.position);
                        if (
                            distance_square < team.vision_radius*team.vision_radius &&
                            distance_square < distance_sq_closest_enemy_flee
                        ){
                            // We must fear this enemy
                            team.enemy_flee_close = true;
                            team.enemy_flee_dir = Vec2::norm(stranger_transform.position - transform.position);
                            distance_sq_closest_enemy_flee = distance_square;
                        }
                    }
                }

                // For each enemy we can attack
                for (auto const & enemy : team.attacks){
                    if (stranger_team.team == enemy){

                        double distance_square = Vec2::dist_sq(transform.position, stranger_transform.position);
                        if (
                            distance_square < team.vision_radius*team.vision_radius &&
                            distance_square < distance_sq_closest_enemy_attack
                        ){
                            // We must attack this enemy
                            team.enemy_attack_close = true;
                            team.enemy_attack_dir = Vec2::norm(stranger_transform.position - transform.position);
                            distance_sq_closest_enemy_attack = distance_square;
                        }
                    }
                }
            }
        }
    }
}