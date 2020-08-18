#pragma once

#include "System.hpp"
#include "MColour.hpp"
#include "Vec2.hpp"

class LightMap;
class LightComponent;
class Game;
class LightSystem : public System{

public:
    LightSystem(Game &game);
    virtual void init() override { };
    virtual void update(double dT) override;

private:
    void add_lighting_to_world();
    void add_lighting_to_entities();
    void update_all_lightsources(double dT);
    void update_lightsource(LightComponent &light, double dT);
    void populate_lightmap();

    void ray_trace_source(Vec2 origin, LightComponent &light, LightMap &lightmap);
    void ray_trace(Vec2 origin, Vec2 direction, LightMap &lightmap, LightComponent &light);
    Vec2 ray_get_next_intersection(Vec2 position, Vec2 direction);
    Vec2 ray_get_propogating_tile(Vec2 position, Vec2 direction);

    void attempt_to_set_colour(int x, int y, LightMap &lightmap, LightComponent &light, double distance_sq);
    MColour get_light_at_distance(LightComponent &light, double distance);
};

