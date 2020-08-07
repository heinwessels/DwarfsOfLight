#pragma once

#include <vector>
#include <cmath>

#include "Tile.hpp"
#include "Renderable.hpp"
#include "LightMap.hpp"

class World{

    const int m_width;
    const int m_height;

    // This is a variable size world.
    // It will be filled with Entities containing only
    // tile and renderable components (for now).
    using Tiles = std::vector<std::vector<Tile>>;
    Tiles m_world;

    LightMap m_lightmap;
    MColour m_global_lighting = {80, 80, 120};

public:
    World (int width, int height);

    Tiles& get_tiles() { return m_world; }
    Tile& get_closest_tile_to(Vec2 point){ return m_world[floor(point.x )][floor(point.y)]; };
    Tile* get_closest_tile_in_range_with_component(Vec2 point, Vec2 range, ComponentID component_ID);

    LightMap& get_light_map() { return m_lightmap; }
    void set_global_lighting(MColour global_lighting) { m_global_lighting = global_lighting; }
    MColour get_global_lighting() { return m_global_lighting; }

private:
    void clear();
    void resize(int width, int height);

};