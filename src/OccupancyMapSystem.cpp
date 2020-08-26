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

    auto &occupancy_map = m_pgame.get_world().get_occupancy_map();

    // Clear the occupancy map
    occupancy_map.clear();

    // Now get a refernece to the grid
    auto &map = occupancy_map.get_map();

    // Now fill the map
    for(auto &entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){

            // Add a pointer to this entity to the corresponding tile
            auto &transform = entity->get_component<TransformComponent>();
            map[floor(transform.position.x)][floor(transform.position.y)].push_back(entity.get());
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