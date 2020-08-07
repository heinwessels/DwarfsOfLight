#pragma once

#include "System.hpp"
#include "Entity.hpp"
#include "Renderable.hpp"
#include "LightComponent.hpp"

class Game;
class LightSystem : public System{

public:
    LightSystem(Game &game);
    virtual void update(float dT) override;

private:
    void add_lighting_to_world();
    void add_lighting_to_entities();
    void update_all_lightsources(float dT);
    void update_lightsource(LightComponent &light, float dT);
    void populate_lightmap();
};

