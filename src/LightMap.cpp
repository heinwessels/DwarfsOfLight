#include "LightMap.hpp"

LightMap::LightMap(int width, int height)
    : m_width(width), m_height(height)
{
    resize(width, height);
}

void LightMap::add_global_lighting(MColour colour){
    for (auto & column : m_lightmap){
        for (auto & light : column){
            light += colour;
        }
    }
}

void LightMap::zero(){
    for (int x = 0; x < m_width; x++)
        for (int y = 0; y < m_height; y++){
            m_lightmap[x][y] = 0;
            m_changedmap[x][y] = false;
        }
}

void LightMap::clamp(){
    for (auto & column : m_lightmap){
        for (auto & colour : column){
            colour.clamp();
        }
    }
}

void LightMap::scale_to_max_channel(){
    for (auto & column : m_lightmap){
        for (auto & colour : column){
            colour.scale_to_max_channel();
        }
    }
}

void LightMap::resize(int width, int height){
    m_width = width;
    m_height = height;

    m_lightmap.resize(width);
    for (auto & column : m_lightmap){
        column.resize(height);
    }

    m_changedmap.resize(width);
    for (auto & column : m_changedmap   ){
        column.resize(height);
    }
}

void LightMap::add_other_light_map(const LightMap & other_map){
    // I'm assuming they're the same size. It's Friday afternoon and I need a beer.
    for (int x = 0; x < m_width; x++)
        for (int y = 0; y < m_height; y++){
            m_lightmap[x][y] += other_map.get_lighting_at(Vec2(x, y));
        }
}