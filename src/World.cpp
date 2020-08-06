#include "World.hpp"

World::World (int width, int height, float grid_size)
        : m_width(width), m_height(height), m_grid_size(grid_size)
{
    clear();
    resize(width, height);


    // RANDOM POPULATE
    ////////////////////////////////////////////////////////
    for (int x = 0; x < m_width; x++)
        for (int y = 0; y < m_width; y++){

            m_world.push_back(Tile(
                m_grid_size / 2.0 + x * m_grid_size,
                m_grid_size / 2.0 + y * m_grid_size
            ));

        }
    ////////////////////////////////////////////////////////
}