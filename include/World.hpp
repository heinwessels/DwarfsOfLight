#pragma once

#include <map>

#include "Tile.hpp"
#include "Renderable.hpp"

class World{

    const int m_width;
    const int m_height;
    const int m_grid_size;

    // This is a variable size world.
    // It will be filled with Entities containing only
    // tile and renderable components (for now).
    std::map<int, Tile> m_world;

public:
    World (int width, int height, float grid_size);

    // Tile& get_tile_at(int x, int y){ return m_world[x*m_width + m_height]; }


private:
    void clear(){ m_world.clear(); }
    void resize_world(int width, int height);

};