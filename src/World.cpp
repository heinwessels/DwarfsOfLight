#include "World.hpp"

World::World (int width, int height, float grid_size)
        : m_width(width), m_height(height), m_grid_size(grid_size)
{
    clear();
    resize_world(m_width, m_height);

}

void World::resize_world(int width, int height){
    // TODO
}
