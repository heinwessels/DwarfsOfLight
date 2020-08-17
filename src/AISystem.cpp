#include "AISystem.hpp"
#include "Game.hpp"

#include "RNG.hpp"


AISystem::AISystem(Game& game)
    : System(game, std::string("AI System"))
{
    m_signature |= Component::get_component_signature(TransformComponentID);
    m_signature |= Component::get_component_signature(PathfindingComponentID);
    m_signature |= Component::get_component_signature(AIComponentID);
}

void AISystem::update(double dT){
    for(auto const entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){
            handle_entity_ai(*entity);
        }
    }
}

void AISystem::handle_entity_ai(Entity& entity){
    // TransformComponent &transform = static_cast<TransformComponent&>(entity.get_component(TransformComponentID));
    PathfindingComponent &pathfinding = static_cast<PathfindingComponent&>(entity.get_component(PathfindingComponentID));
    AIComponent &ai = static_cast<AIComponent&>(entity.get_component(AIComponentID));


    auto &world = m_pgame.get_world();

    if(ai.get_mode() == AIComponent::ModeWandering &&
        !(pathfinding.is_path_requested() || pathfinding.is_moving_to_target())
    ){
        // Wonder randomly to some location

        // Find a random location
        bool valid = false;
        Vec2 target = {-1, -1};
        while(!valid){
            target.x = random_float_in_range(0, world.get_width()) + 0.5;
            target.y = random_float_in_range(0, world.get_height()) + 0.5;

            if (world.get_closest_tile_to(target).get_type() == Tile::TypeFloor){
                valid = true;
            }
        }

        // Set this entity to move there
        pathfinding.go_to_target(target);
    }
}