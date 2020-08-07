#pragma once

#include <vector>
#include <cmath>

#include "Tile.hpp"
#include "Renderable.hpp"

class World{

    const int m_width;
    const int m_height;

    // This is a variable size world.
    // It will be filled with Entities containing only
    // tile and renderable components (for now).
    using Tiles = std::vector<std::vector<Tile>>;
    Tiles m_world;

    using LightMap = std::vector<std::vector<int>>;
    LightMap m_light_map;
    int m_global_lighting;

public:
    World (int width, int height);

    Tiles& get_tiles() { return m_world; }
    Tile& get_closest_tile_to(Vec2 point);
    Tile* get_closest_tile_in_range_with_component(Vec2 point, Vec2 range, ComponentID component_ID);

    void set_global_lighting(int global_lighting) { m_global_lighting = global_lighting; }
    void add_global_lighting();
    void clear_light_map();

private:
    void clear();
    void resize(int width, int height);

};