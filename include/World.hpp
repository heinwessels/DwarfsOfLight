#pragma once

#include <vector>
#include <cmath>

#include "Tile.hpp"
#include "Renderable.hpp"

class World{

    const int m_width;
    const int m_height;
    const float m_grid_size;

    // This is a variable size world.
    // It will be filled with Entities containing only
    // tile and renderable components (for now).
    std::vector<Tile> m_world;

public:
    World (int width, int height, float grid_size);

    Tile& get_tile_at(int x, int y){ return m_world[x*m_width + y]; }   // There should always be a tile at that location
    std::vector<Tile>& get_tiles() { return m_world; }
    Tile& get_closest_tile(Vec2 point);

private:
    void clear(){ m_world.clear(); }
    void resize(int width, int height){ m_world.reserve(width * height); }

};