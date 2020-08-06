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

            m_world.push_back(Tile(
                type,
                m_grid_size / 2.0 + x * m_grid_size,
                m_grid_size / 2.0 + y * m_grid_size
            ));

        }
    ////////////////////////////////////////////////////////
}

Tile& World::get_closest_tile(Vec2 point){
    return get_tile_at(
        floor(point.x / m_grid_size),
        floor(point.y / m_grid_size)
    );
}