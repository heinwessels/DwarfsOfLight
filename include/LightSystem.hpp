#pragma once

#include <list>
#include <utility>

#include "Tile.hpp"
#include "LightMap.hpp"
#include "System.hpp"
#include "Entity.hpp"
#include "Renderable.hpp"
#include "LightComponent.hpp"

class Seed {public: int x, y; Seed(int x, int y) : x(x), y(y) { }};

class Game;
class LightSystem : public System{

    using World = std::vector<std::vector<Tile>>;

public:
    LightSystem(Game &game);
    virtual void update(float dT) override;

private:
    void add_lighting_to_world();
    void add_lighting_to_entities();
    void update_all_lightsources(float dT);
    void update_lightsource(LightComponent &light, float dT);
    void populate_lightmap();

    void grow_light_source(LightMap &lightmap, const LightComponent light, Vec2 origin);
    std::list<Seed> grow_light_seed(Seed source, Vec2 origin, LightMap& lightmap, LightComponent light);
    std::list<Seed> get_neighbour_seeds_in_direction(Seed seed, float angle);
};

