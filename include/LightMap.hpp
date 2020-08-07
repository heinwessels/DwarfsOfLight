#pragma once

#include <vector>

#include "MColour.hpp"
#include "Vec2.hpp"

class LightMap{

    using LightMap_t = std::vector<std::vector<MColour>>;
    LightMap_t m_lightmap;

    int m_width, m_height;

public:
    LightMap (int width, int height);

    MColour get_lighting_at(Vec2 point) { return m_lightmap[floor(point.x)][floor(point.y)]; }

    void add_global_lighting(MColour colour);
    void zero();
    void resize(int width, int height);
};