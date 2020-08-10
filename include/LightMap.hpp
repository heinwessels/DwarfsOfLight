#pragma once

#include <vector>

#include "MColour.hpp"
#include "Vec2.hpp"

class LightMap{

    using LightMap_t = std::vector<std::vector<MColour>>;
    LightMap_t m_lightmap;

    using ChangedMap = std::vector<std::vector<bool>>;
    ChangedMap m_changedmap;  // To aid during light growing algorithm

    int m_width, m_height;

public:
    LightMap (int width, int height);

    void set_lighting_at(int x, int y, MColour c) { m_lightmap[x][y] = c; m_changedmap[x][y] = true; }
    MColour get_lighting_at(Vec2 point) const { return m_lightmap[floor(point.x)][floor(point.y)]; }
    bool has_been_modifed(int x, int y) { return m_changedmap[x][y]; }

    void add_global_lighting(MColour colour);
    void zero();
    void clamp();

    void resize(int width, int height);
    int get_width() { return m_width; }
    int get_height() { return m_height; }


    LightMap& operator += (const LightMap & lightmap){
        add_other_light_map(lightmap);
        return *this;
    }
    LightMap operator + (const LightMap &v) const{
        LightMap t (*this);
        t += v;
        return t;
    }

private:
    void add_other_light_map(const LightMap & other_map);
};