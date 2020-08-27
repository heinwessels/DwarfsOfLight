#pragma once

#include <vector>
#include <string>

#include "Tile.hpp"
#include "LightMap.hpp"
#include "OccupancyMapSystem.hpp"

class World{

    int m_width;
    int m_height;

    // This is a variable size world.
    // It will be filled with Entities containing only
    // tile and renderable components (for now).
    std::vector<std::vector<Tile>> m_world;

    LightMap m_lightmap;
    MColour m_global_lighting = {0, 0, 0};

    OccupancyMap m_occupancymap;

public:
    World (int width, int height);
    World (std::string map_path);

    std::vector<std::vector<Tile>>& get_tiles();
    Tile& get_closest_tile_to(Vec2 point);

    LightMap& get_light_map();
    void set_global_lighting(MColour global_lighting);
    MColour get_global_lighting();

    OccupancyMap &get_occupancy_map(){ return m_occupancymap; }

    void load_world(std::string path);
    void add_tile_at(int x, int y, Tile::Type type);

    int get_width() const;
    int get_height() const;

    bool within_bounds(int x, int y){
        return 0 <= x && x < m_width && 0 <= y && y < m_height;
    }

private:
    void clear();
    void resize(int width, int height);
};