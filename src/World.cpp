#include "World.hpp"

World::World (int width, int height, float grid_size)
        : m_width(width), m_height(height), m_grid_size(grid_size)
{
    clear();
    resize(width, height);


    // RANDOM POPULATE
    ////////////////////////////////////////////////////////
    for (int y = 0; y < m_height; y++)
        for (int x = 0; x < m_width; x++){

            Tile::Type type = Tile::TypeAir;
            if (x == 3 || x == 19){
                type = Tile::TypeWall;
            }

            m_world[x][y] = Tile(
                type,
                m_grid_size / 2.0 + x * m_grid_size,
                m_grid_size / 2.0 + y * m_grid_size
            );

        }
    ////////////////////////////////////////////////////////
}

Tile& World::get_closest_tile_to(Vec2 point){
    return m_world[floor(point.x / m_grid_size)][floor(point.y / m_grid_size)];
}

Tile* World::get_closest_tile_in_range_with_component(Vec2 point, Vec2 range, ComponentID component_ID){
    // <range> is size of square around <point>
    // Returns <nullptr> if none found.

    Tile* closest_tile = nullptr; // Empty tile
    float closest_distance_sq = 1e8;
    Vec2 bottom_left = point - range / 2;
    Vec2 top_right = point + range / 2;
    for (int x = floor(bottom_left.x/m_grid_size); x <= ceil(top_right.x/m_grid_size); x ++){
        for (int y = floor(bottom_left.y/m_grid_size); y <= ceil(top_right.y/m_grid_size); y ++){

            if(m_world[x][y].has_component(component_ID)){

                float dist_sq = Vec2::dist_sq(point, m_world[x][y].get_posision());

                if(dist_sq < closest_distance_sq){
                    closest_distance_sq = dist_sq;
                    closest_tile = &m_world[x][y];
                }
            }
        }
    }

    return closest_tile;
}

void World::clear(){
    for (auto & column : m_world)
        column.clear();
    m_world.clear();
}
void World::resize(int width, int height){
    m_world.resize(width);
    for (auto & column : m_world){
        column.resize(height);
    }
}