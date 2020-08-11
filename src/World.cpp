#include "World.hpp"

World::World (int width, int height)
        : m_lightmap(width, height), m_width(width), m_height(height)
{
    clear();
    resize(width, height);


    // RANDOM POPULATE
    ////////////////////////////////////////////////////////
    for (int y = 0; y < m_height; y++)
        for (int x = 0; x < m_width; x++){

            Tile::Type type = Tile::TypeFloor;
            // if (
            //     (x == 13 && y > 12)
            //     || (x == 25 && y != 12)
            //     || (x == 13 && y == 5)
            //     || (x == 30 && (y == 13 || y == 14))
            // ){
            //     type = Tile::TypeWall;
            // }

            m_world[x][y] = Tile(
                type,
                x + 0.5f, y + 0.5f
            );  // + 0.5 to center the tile in the middle of the grid. (I think, we'll see)

        }
    ////////////////////////////////////////////////////////
}

Tile* World::get_closest_tile_in_range_with_component(Vec2 point, Vec2 range, ComponentID component_ID){
    // <range> is size of square around <point>
    // Returns <nullptr> if none found.

    Tile* closest_tile = nullptr; // Empty tile
    double closest_distance_sq = 1e8;
    Vec2 bottom_left = point - range / 2;
    Vec2 top_right = point + range / 2;
    for (int x = floor(bottom_left.x); x <= ceil(top_right.x); x ++){
        for (int y = floor(bottom_left.y); y <= ceil(top_right.y); y ++){

            if(m_world[x][y].has_component(component_ID)){

                double dist_sq = Vec2::dist_sq(point, m_world[x][y].get_posision());

                if(dist_sq < closest_distance_sq){
                    closest_distance_sq = dist_sq;
                    closest_tile = &m_world[x][y];
                }
            }
        }
    }

    return closest_tile;
}

void World::clear(){
    for (auto & column : m_world){
        column.clear();
    }
    m_world.clear();

}
void World::resize(int width, int height){
    m_world.resize(width);
    for (auto & column : m_world){
        column.resize(height);
    }
}