#include "OccupancyMapSystem.hpp"
#include "Game.hpp"
#include "World.hpp"

#include "Entity.hpp"
#include "TransformComponent.hpp"

OccupancySystem::OccupancySystem(Game &game)
    :   System(game, std::string("Moving System"))
{
    m_signature |= Component::get_component_signature<TransformComponent>();
}

void OccupancySystem::update(double dT){

    auto &world = m_pgame.get_world();

    // Clear the occupancy map
    world.get_occupancy_map().clear();

    // Now get a refernece to the grid
    auto &map = world.get_occupancy_map().get_map();

    // Now fill the map
    for(auto &entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){

            // Add a pointer to this entity to the corresponding tile
            auto &transform = entity->get_component<TransformComponent>();

            // Just a quick sanity check
            int x = floor(transform.position.x), y = floor(transform.position.y);
            if (world.within_bounds(x, y)){
                // This is a valid location
                map[x][y].push_back(entity.get());
            }
            // else
            //  Some entity did something stupid, and is now outside the map
        }
    }
}

OccupancyMap::OccupancyMap(int width, int height)
    : m_width(width), m_height(height)
{
    resize(width, height);
}

void OccupancyMap::clear(){
    for (int x = 0; x < m_width; x++)
        for (int y = 0; y < m_height; y++){
            m_map[x][y].clear();
        }
}

void OccupancyMap::resize(int width, int height){
    m_width = width;
    m_height = height;

    m_map.resize(width);
    for (auto & column : m_map){
        column.resize(height);
    }
}

std::list<Entity*> OccupancyMap::find_entities_in_range(World &world, Vec2 position, Vec2 range){
    auto &map = world.get_occupancy_map().get_map();

    std::list<Entity*> entities;

    Vec2 lower_left = {
        std::max(0.0, floor(position.x - range.x/2.0)),
        std::max(0.0, floor(position.y - range.y/2.0))
    };
    Vec2 upper_right = {
        std::min(floor(position.x + range.x/2.0), (double) world.get_width()),
        std::min(floor(position.y + range.y/2.0), (double) world.get_height())
    };

    for (int x = lower_left.x; x < upper_right.x; x ++)
        for (int y = lower_left.y; y < upper_right.y; y ++){
            // For every tile in the map

            // Copy pointers to all the entities to on this tile to <entities>
            std::copy(map[x][y].begin(), map[x][y].end(), std::back_inserter(entities));
        }

    return entities;
}