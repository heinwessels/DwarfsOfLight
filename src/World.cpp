#include "World.hpp"

#include "Renderable.hpp"

#include <cmath>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <boost/algorithm/string.hpp>

World::World (int width, int height)
        : m_width(width), m_height(height), m_lightmap(width, height)
{

    clear();
    resize(width, height);


    // RANDOM POPULATE
    ////////////////////////////////////////////////////////
    for (int y = 0; y < m_height; y++)
        for (int x = 0; x < m_width; x++){

            Tile::Type type = Tile::TypeFloor;
            if (
                (x == 13 && y > 12)
                || (x == 25 && y != 12)
                || (x == 13 && y == 5)
                || (x == 30 && (y == 13 || y == 14))
            ){
                type = Tile::TypeWall;
            }

            add_tile_at(x, y, type);
        }
    ////////////////////////////////////////////////////////
}

World::World (std::string map_path)
    : World(0, 0)
{
    load_world(map_path);
}


std::vector<std::vector<Tile>>& World::get_tiles() { return m_world; }
Tile& World::get_closest_tile_to(Vec2 point){ return m_world[floor(point.x )][floor(point.y)]; };

LightMap& World::get_light_map() { return m_lightmap; }
void World::set_global_lighting(MColour global_lighting) { m_global_lighting = global_lighting; }
MColour World::get_global_lighting() { return m_global_lighting; }

int World::get_width() const { return m_width; }
int World::get_height()const { return m_height; }


void World::add_tile_at(int x, int y, Tile::Type type) {
    m_world[x][y] = Tile(
        type,
        x + 0.5f,
        y + 0.5f
    );  // + 0.5 to center the tile in the middle of the grid.
}

void World::clear(){
    for (auto & column : m_world){
        column.clear();
    }
    m_world.clear();

}
void World::resize(int width, int height){
    m_width = width;
    m_height = height;
    m_world.resize(width);
    for (auto & column : m_world){
        column.resize(height);
    }
    m_lightmap.resize(width, height);
}


void World::load_world(std::string path){

    // Reset the current world
    clear();

    // Read the data
    std::vector<std::vector<std::string> > tile_map;
    std::ifstream file(path);
    std::string line = "";
    while (getline(file, line))
    {
        std::vector<std::string> line_vec;
        boost::algorithm::split(line_vec, line, boost::is_any_of(";"));
        tile_map.push_back(line_vec);
    }

    // Close the File
    file.close();

    // Now unpack the data
    resize(tile_map[0].size(), tile_map.size());
    for(int y = 0; y < m_height; y ++){
        for (int x = 0; x < m_width; x ++){
            add_tile_at(
                x, y,
                std::stoi(tile_map[y][x]) /* It's transposed */
            );
        }
    }
}
