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
    for (auto & column : m_lightmap){
        for (auto & tile : column){
            tile = MColour(0.0);
        }
    }
}

void LightMap::resize(int width, int height){
    m_lightmap.resize(width);
    for (auto & column : m_lightmap){
        column.resize(height);
    }
}
