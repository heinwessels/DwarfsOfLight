#include "AISystem.hpp"
#include "Game.hpp"
#include "World.hpp"

#include "RNG.hpp"
#include "Vec2.hpp"

#include "TransformComponent.hpp"
#include "PathfindingComponent.hpp"
#include "AIComponent.hpp"

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
    // TODO This is probably temporary

    // TransformComponent &transform = static_cast<TransformComponent&>(entity.get_component(TransformComponentID));
    PathfindingComponent &pathfinding = entity.get_component<PathfindingComponent>();
    AIComponent &ai = entity.get_component<AIComponent>();

    auto &world = m_pgame.get_world();

    if(ai.get_mode() == AIComponent::ModeWandering &&
        !(pathfinding.path_requested || pathfinding.moving_to_target)
    ){
        // Wonder randomly to some location

        // Find a random location
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