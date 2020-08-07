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

    using LightMap = std::vector<std::vector<MColour>>;
    LightMap m_light_map;
    MColour m_global_lighting = {80, 80, 120};

public:
    World (int width, int height);

    Tiles& get_tiles() { return m_world; }
    Tile& get_closest_tile_to(Vec2 point){ return m_world[floor(point.x )][floor(point.y)]; };
    Tile* get_closest_tile_in_range_with_component(Vec2 point, Vec2 range, ComponentID component_ID);

    MColour get_lighting_at(Vec2 point){ return m_light_map[floor(point.x )][floor(point.y)]; };
    void set_global_lighting(MColour global_lighting) { m_global_lighting = global_lighting; }
    void add_global_lighting();
    void reset_light_map();

private:
    void clear();
    void resize(int width, int height);

};