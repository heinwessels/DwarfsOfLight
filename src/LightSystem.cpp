#include "LightSystem.hpp"
#include "Game.hpp"

LightSystem::LightSystem(Game &game)
    :   System(game)
{
    m_signature |= Component::get_component_signature(LightComponentID);
}

void LightSystem::update(float dT){

    // update_all_lightsource_seeds(dT);
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

    // Calculate the light created by all entities with light
    for(auto const &entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){
            LightComponent &light = static_cast<LightComponent&>(entity->get_component(LightComponentID));

            // TODO This will only work with ONE LIGHT
            ray_trace_source(entity->get_posision(), light, lightmap);
        }
    }

    // lightmap.add_global_lighting(m_pgame.get_world().get_global_lighting());
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

void LightSystem::ray_trace_source(Vec2 origin, LightComponent &light, LightMap &lightmap){

    static const int num_of_rays = 12;
    for (float angle = 0; angle < 2 * M_PI; angle += 2 * M_PI / num_of_rays){

        printf("\nAngle %.3f: ", angle * 180 / M_PI);

        ray_trace(
            origin,
            Vec2(cosf(angle), sinf(angle)),
            lightmap,
            light
        );
    }
}

void LightSystem::ray_trace(Vec2 origin, Vec2 direction, LightMap &lightmap, LightComponent &light){

    Vec2 current_position = origin;
    World &world = m_pgame.get_world().get_tiles();

    bool end_ray = false;
    while(!end_ray){

        // Get the current tile we're working with
        int x = floor(current_position.x);
        int y = floor(current_position.y);

        // If this tile has not been modified, and receives light, update!
        if (lightmap.has_been_modifed(x, y)){
            // It has not been modified!

            // Update the light at this tile
            lightmap.set_lighting_at(x, y, light.base_colour);
            lightmap.modify(x, y);  // This is an unnesary step. Should be part of <set_lighting_at>
        }

        // Now propogate the ray
        current_position = ray_get_next_intersection(current_position, direction);

        // Get the new tile we're working with (TODO Can be optimized)
        x = floor(current_position.x);
        y = floor(current_position.y);

        // Verify this ray is still valid
        if (Vec2::dist_sq(origin, current_position) > light.max_dist*light.max_dist){
            // It can't travel any further
            end_ray = true;
        }
        else if (world[x][y].get_type() == Tile::TypeAir){
            // We've reached a light blocking block
            end_ray = true;
        }

        // printf(".");
        printf("Dist: %.3f\n", sqrt(Vec2::dist_sq(origin, current_position)));
    }
}

Vec2 LightSystem::ray_get_next_intersection(Vec2 position, Vec2 direction){

    // Should we transpose to avoid infinities at vertical lines when direction > 45 degrees
    bool transposed = abs(direction.y) > abs(direction.x);
    Vec2 position_ = transposed ? Vec2::transpose(position) : position;
    Vec2 direction_ = transposed ? Vec2::transpose(direction) : direction;

    // Finish the straight line equation < y=mx+c >
    float m = direction_.y / direction_.x;
    float c = position_.y - m * position_.x;

    // Get the tile we're currently working with
    Vec2 current_tile_ = Vec2::floor(position_); // Could this give the wrong number on edge cases?

    // TODO FIX HERE! The current tile gives the wrong result under certain conditions.

    // Now find the next intersection on the current tile edge (whole number)
    // Remember to verify that you don't return the same edge by looking at the ray direction!
    // TODO This can be optimized by calculating the new possible coordinate once, instead of twice
    Vec2 new_intersection_ = position_;
    if (
        /* Left edge */
        (current_tile_.y <= (m*(current_tile_.x) + c)) && ((m*(current_tile_.x) + c) <= (current_tile_.y + 1))
        && (direction_.x < 0)
    ){
        new_intersection_ = Vec2(current_tile_.x, m*(current_tile_.x) + c);
    }
    else if (
        /* Right edge */
        (current_tile_.y <= (m*(current_tile_.x + 1) + c)) && ((m*(current_tile_.x + 1) + c) <= (current_tile_.y + 1))
        && (direction_.x > 0)
    ){
        new_intersection_ = Vec2(current_tile_.x + 1, m*(current_tile_.x + 1) + c);
    }
    else if (
        /* Bottom edge */
        (current_tile_.x <= ((current_tile_.y - c)/m) && ((current_tile_.y - c)/m) <= (current_tile_.x + 1))
        && (direction_.y < 0)
    ){
        new_intersection_ = Vec2((current_tile_.y - c)/m, current_tile_.y);
    }
    else if (
        /* Bottom edge */
        (current_tile_.x <= ((current_tile_.y + 1 - c)/m) && ((current_tile_.y + 1 - c)/m) <= (current_tile_.x + 1))
        && (direction_.y > 0)
    ){
        new_intersection_ = Vec2((current_tile_.y + 1 - c)/m, current_tile_.y + 1);
    }
    else{
        // It should never reach this!
        printf("ERROR: Ray tracing couldn't find next tile! (Position = [%.3f, %.3f], Direction = [%.3f, %.3f]\n",
            position.x, position.y, direction.x, direction.y
        );
    }

    // Now return the transposed result
    return transposed ? Vec2::transpose(new_intersection_) : new_intersection_;
}