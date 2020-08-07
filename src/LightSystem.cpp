#include "LightSystem.hpp"
#include "Game.hpp"

LightSystem::LightSystem(Game &game)
    :   System(game)
{
    m_signature |= Component::get_component_signature(LightComponentID);
}

void LightSystem::update(float dT){

    // update_all_lightsources(dT);
    populate_lightmap();

    add_lighting_to_world();
    add_lighting_to_entities();
}

void LightSystem::add_lighting_to_world(){

    LightMap& lightmap = m_pgame.get_world().get_light_map();

    for (auto & column : m_pgame.get_world().get_tiles()){
        for (auto & tile : column){
            if (tile.has_component(RenderComponentID)){

                Renderable &renderable = static_cast<Renderable&>(tile.get_component(RenderComponentID));
                renderable.get_mtexture().setColor(
                    lightmap.get_lighting_at(tile.get_posision())
                );
            }
        }
    }
}

void LightSystem::add_lighting_to_entities(){

    LightMap& lightmap = m_pgame.get_world().get_light_map();

    for(auto const &entity : m_pgame.get_entities()){
        if (entity->has_component(RenderComponentID)){
            Renderable &renderable = static_cast<Renderable&>(entity->get_component(RenderComponentID));
            renderable.get_mtexture().setColor(
                lightmap.get_lighting_at(entity->get_posision())
            );
        }
    }
}

void LightSystem::populate_lightmap(){

    LightMap& lightmap = m_pgame.get_world().get_light_map();

    lightmap.zero();

    lightmap.add_global_lighting(m_pgame.get_world().get_global_lighting());
}

void LightSystem::update_all_lightsources(float dT){
    for(auto const &entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){

            LightComponent &light = static_cast<LightComponent&>(entity->get_component(LightComponentID));
            update_lightsource(light, dT);

        }
    }
}

void LightSystem::update_lightsource(LightComponent &light, float dT){

    light.current_colour += light.colour_weight * dT * 128;

    if(light.current_colour.r > 255)
        light.current_colour.r = 0;
    if(light.current_colour.g > 255)
        light.current_colour.g = 0;
    if(light.current_colour.b > 255)
        light.current_colour.b = 0;
}