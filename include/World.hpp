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
    using Tiles = std::vector<std::vector<Tile>>;
    Tiles m_world;

public:
    World (int width, int height, float grid_size);

    Tiles& get_tiles() { return m_world; }
    Tile& get_closest_tile_to(Vec2 point);
    Tile* get_closest_tile_in_range_with_component(Vec2 point, Vec2 range, ComponentID component_ID);


private:
    void clear();
    void resize(int width, int height);

};