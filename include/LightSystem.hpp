#pragma once

#include <list>
#include <utility>

#include "Tile.hpp"
#include "LightMap.hpp"
#include "System.hpp"
#include "Entity.hpp"
#include "Renderable.hpp"
#include "LightComponent.hpp"

class Game;
class LightSystem : public System{

    using World = std::vector<std::vector<Tile>>;

public:
    LightSystem(Game &game);
    virtual void internal_update(float dT) override;

private:
    void add_lighting_to_world();
    void add_lighting_to_entities();
    void update_all_lightsources(float dT);
    void update_lightsource(LightComponent &light, float dT);
    void populate_lightmap();

    void ray_trace_source(Vec2 origin, LightComponent &light, LightMap & lightmap);
    void ray_trace(Vec2 origin, Vec2 direction, LightMap &lightmap, LightComponent &light);
    Vec2 ray_get_next_intersection(Vec2 position, Vec2 direction);
    Vec2 ray_get_propogating_tile(Vec2 position, Vec2 direction);
};

