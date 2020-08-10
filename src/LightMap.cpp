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
    m_lightmap.clear();
    m_changedmap.clear();

    resize(m_width, m_height);
}

void LightMap::clamp(){
    for (auto & column : m_lightmap){
        for (auto & colour : column){
            colour.clamp();
        }
    }
}

void LightMap::resize(int width, int height){
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