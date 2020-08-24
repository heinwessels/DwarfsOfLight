// #define DBG_PRINT_BASIC_INFO

#include "AISystem.hpp"
#include "Game.hpp"
#include "World.hpp"

#include "RNG.hpp"
#include "Vec2.hpp"

#include "TransformComponent.hpp"
#include "MoveComponent.hpp"
#include "PathfindingComponent.hpp"
#include "AIComponent.hpp"
#include "TeamComponent.hpp"

AISystem::AISystem(Game& game)
    : System(game, std::string("AI System"))
{
    m_signature |= Component::get_component_signature<TransformComponent>();
    m_signature |= Component::get_component_signature<MoveComponent>();
    m_signature |= Component::get_component_signature<PathfindingComponent>();
    m_signature |= Component::get_component_signature<AIComponent>();
}

void AISystem::update(double dT){
    for(auto const entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){
            handle_entity_ai(*entity);
        }
    }
}

void AISystem::handle_entity_ai(Entity& entity){
    // TODO This is probably temporary

    // TransformComponent &transform = static_cast<TransformComponent&>(entity.get_component(TransformComponentID));
    auto &move = entity.get_component<MoveComponent>();
    auto &pathfinding = entity.get_component<PathfindingComponent>();
    auto &ai = entity.get_component<AIComponent>();

    // Is this entity part of a team?
    TeamComponent *team = nullptr;
    if (entity.has_component<TeamComponent>()){
        team = &entity.get_component<TeamComponent>();
    }

    if(ai.mode == AIComponent::ModeWandering){

        // First see if we should rather flee or attack
        if (team && team->enemy_flee_close){
            // We should flee! (rather priority over attack)
            ai.mode = AIComponent::ModeFlee;
#ifdef DBG_PRINT_BASIC_INFO
            printf("%15s is now fleeing.\n", entity.get_name().c_str());
#endif
        }
        else if (team->enemy_attack_close){
            // We should attack!
            ai.mode = AIComponent::ModeAttack;
#ifdef DBG_PRINT_BASIC_INFO
            printf("%15s is now attacking.\n", entity.get_name().c_str());
#endif
        }
        else{
            // Nothing is going on. Just continue wandering
            wandering_continue(pathfinding);
        }
    }
    else if (ai.mode == AIComponent::ModeAttack){

        // First see if we should rather flee
        if (team && team->enemy_flee_close){
            // We should flee! (rather priority over attack)
            ai.mode = AIComponent::ModeFlee;
#ifdef DBG_PRINT_BASIC_INFO
            printf("%15s is now fleeing.\n", entity.get_name().c_str());
#endif
        }
        else if (team && team->enemy_attack_close){
            // The enemy is still close

            // Charge the target!
            move.target_direction = team->enemy_attack_dir;

            // Disable pathfinding
            pathfinding.moving_to_target = false;
        }
        else{
            // Start wandering again
            ai.mode = AIComponent::ModeWandering;
            wandering_continue(pathfinding);
#ifdef DBG_PRINT_BASIC_INFO
            printf("%15s is now wandering.\n", entity.get_name().c_str());
#endif
        }
    }
    else if (ai.mode == AIComponent::ModeFlee){

        if (team && team->enemy_flee_close){
            // Run in the opposite way of the danger
            // TODO: Handle when running into walls
            move.target_direction = Vec2(0) - team->enemy_flee_dir;

            // Disable pathfinding
            pathfinding.moving_to_target = false;
        }
        else{
            // No more threat. Start wandering again.
            ai.mode = AIComponent::ModeWandering;
            wandering_continue(pathfinding);
#ifdef DBG_PRINT_BASIC_INFO
            printf("%15s is now wandering.\n", entity.get_name().c_str());
#endif
        }
    }
}

void AISystem::wandering_continue(PathfindingComponent &pathfinding){
    // Just let the entity continue to wander randomly

    if (!(pathfinding.path_requested || pathfinding.moving_to_target)){
        // It need a new place to walk to

        auto &world = m_pgame.get_world();

        bool valid = false;
        Vec2 target = {-1, -1};
        while(!valid){
            target.x = random_float_in_range(0, world.get_width());
            target.y = random_float_in_range(0, world.get_height());

            if (world.get_closest_tile_to(target).get_type() == Tile::TypeFloor){
                valid = true;
            }
        }

        // Set this entity to move there
        pathfinding.target = target + 0.5;
        pathfinding.path_requested = true;
    }
}