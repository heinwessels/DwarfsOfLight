#include "LightSystem.hpp"
#include "Game.hpp"
#include "World.hpp"

#include "RNG.hpp"

#include "LightMap.hpp"
#include "Entity.hpp"
#include "Renderable.hpp"
#include "LightComponent.hpp"

LightSystem::LightSystem(Game &game)
    :   System(game, std::string("Lighting System"))
{
    m_signature |= Component::get_component_signature<TransformComponent>();
    m_signature |= Component::get_component_signature<LightComponent>();
}

void LightSystem::update(double dT){

    update_all_lightsources(dT);
    populate_lightmap();

    add_lighting_to_world();
    add_lighting_to_entities();
}

void LightSystem::add_lighting_to_world(){

    LightMap& lightmap = m_pgame.get_world().get_light_map();

    for (auto & column : m_pgame.get_world().get_tiles()){
        for (auto & tile : column){
            if (tile.has_component<Renderable>()){

                TransformComponent &transform = tile.get_component<TransformComponent>();
                Renderable &renderable = tile.get_component<Renderable>();

                renderable.set_colour_mod(
                    lightmap.get_lighting_at(transform.position)
                );
            }
        }
    }
}

void LightSystem::add_lighting_to_entities(){

    LightMap& lightmap = m_pgame.get_world().get_light_map();

    for(auto const &entity : m_pgame.get_entities()){
        if (entity->has_component<Renderable>()){
            TransformComponent &transform = entity->get_component<TransformComponent>();
            Renderable &renderable = entity->get_component<Renderable>();
            renderable.set_colour_mod(
                lightmap.get_lighting_at(transform.position)
            );
        }
    }
}

void LightSystem::populate_lightmap(){

    LightMap& lightmap = m_pgame.get_world().get_light_map();
    lightmap.zero();

    // Calculate the light created by all entities with light
    LightMap new_lightmap = LightMap(lightmap.get_width(), lightmap.get_height());
    for(auto const &entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){
            TransformComponent &transform = entity->get_component<TransformComponent>();
            LightComponent &light = entity->get_component<LightComponent>();

            // Calculate the lightmap of this lightsource
            new_lightmap.zero();
            ray_trace_source(transform.position, light, new_lightmap);
            lightmap += new_lightmap;   // TODO This doesn't merge colours nicely.
        }
    }

    lightmap.add_global_lighting(m_pgame.get_world().get_global_lighting());
    lightmap.clamp();   // Ensure all lightmap values are between 0 and 255
}

void LightSystem::update_all_lightsources(double dT){
    for(auto const &entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){

            LightComponent &light = entity->get_component<LightComponent>();
            update_lightsource(light, dT);
        }
    }
}

void LightSystem::update_lightsource(LightComponent &light, double dT){

    // Change the gradient based on the frequency
    light.time_to_gradient_change -= dT;
    if (light.time_to_gradient_change < 0.0){

        // Calculate the new colour target
        MColour target_colour = MColour(
            light.base_colour.r + random_float_in_range(-light.colour_variation.r, light.colour_variation.r),
            light.base_colour.g + random_float_in_range(-light.colour_variation.g, light.colour_variation.g),
            light.base_colour.b + random_float_in_range(-light.colour_variation.b, light.colour_variation.b)
        );
        target_colour.clamp();  // Make sure it's valid

        // Calculate the new period
        light.time_to_gradient_change = light.period + random_float_in_range(-1, 1) * light.period * 0.5;   // 30% variation

        // Calculate the new
        light.current_gradient = (target_colour - light.current_colour) / light.time_to_gradient_change;
    }

    // Now follow this gradient
    light.current_colour += light.current_gradient * dT;
    light.current_colour.clamp();
}

void LightSystem::ray_trace_source(Vec2 origin, LightComponent &light, LightMap &lightmap){

    static const int num_of_rays = 200;
    for (double angle = 0; angle < 2 * M_PI; angle += 2 * M_PI / num_of_rays){

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
    auto &world = m_pgame.get_world().get_tiles();

    // Get the current tile we're working with
    Vec2 current_tile = ray_get_propogating_tile(current_position, direction);
    int current_x = floor(current_tile.x);
    int current_y = floor(current_tile.y);

    // We might not trigger the source block, so ensure it's coloured in.
    attempt_to_set_colour(current_x, current_y, lightmap, light, 0);    // Assume zero distance

    bool end_ray = false;
    while(!end_ray){

        // Propogate the ray
        current_position = ray_get_next_intersection(current_position, direction);

        // Get the new tile we're working with
        current_tile = ray_get_propogating_tile(current_position, direction);
        current_x = round(current_tile.x);
        current_y = round(current_tile.y);

        // Verify this ray is still valid
        if (
            current_x < 0 || (current_x > lightmap.get_width() - 1) ||
            current_y < 0 || (current_y > lightmap.get_height() - 1)
        ){
            // The ray is going out of bounds
            end_ray = true;
        }
        else {

            // Calculate distance to this tile
            // Because that where we need the ligth value from
            double dist_sq = Vec2::dist_sq(origin, Vec2(current_x + 0.5, current_y + 0.5)); // <+0.5> to go from index to MIDDLE of tile

            if (dist_sq > light.range*light.range){
                // It can't travel any further.
                end_ray = true;
            }

            // We know now that this tile must have light
            attempt_to_set_colour(current_x, current_y, lightmap, light, dist_sq);

            if (world[current_x][current_y].get_type() == Tile::TypeWall){
                // If we reached a wall, it must not propogate again. (We did need to draw it)
                end_ray = true;
            }
        }
    }
}

void LightSystem::attempt_to_set_colour(int x, int y, LightMap &lightmap, LightComponent &light, double distance_sq){
    // First check if this tile has been modified
    if (!lightmap.has_been_modifed(x, y)){
        lightmap.set_lighting_at(
            x, y,
            get_light_at_distance(light, sqrtf(distance_sq))
        );
    }
}

Vec2 LightSystem::ray_get_next_intersection(Vec2 position, Vec2 direction){

    const double tolerance = 1e-6;    // This is because whole numbers aren't always exact.

    // Should we transpose to avoid infinities at vertical lines when direction > 45 degrees
    bool transposed = abs(direction.y) > abs(direction.x);
    Vec2 position_ = transposed ? Vec2::transpose(position) : position;
    Vec2 direction_ = transposed ? Vec2::transpose(direction) : direction;

    // Finish the straight line equation < y=mx+c >
    double m = direction_.y / direction_.x;
    double c = position_.y - m * position_.x;

    // Get the tile we're currently working with
    Vec2 current_tile_ = ray_get_propogating_tile(position_, direction_);

    // Now find the next intersection on the current tile edge (whole number)
    // Remember to verify that you don't return the same edge by looking at the ray direction!
    // TODO This can be optimized by calculating the new possible coordinate once, instead of twice
    Vec2 new_intersection_ = position_;
    if (+
        /* Left edge */
        (current_tile_.y - tolerance <= (m*(current_tile_.x) + c)) && ((m*(current_tile_.x) + c) <= (current_tile_.y + 1 + tolerance))
        && (direction_.x < 0)
    ){
        new_intersection_ = Vec2(current_tile_.x, m*(current_tile_.x) + c);
    }
    else if (
        /* Right edge */
        (current_tile_.y - tolerance <= (m*(current_tile_.x + 1) + c)) && ((m*(current_tile_.x + 1) + c) <= (current_tile_.y + 1 + tolerance))
        && (direction_.x > 0)
    ){
        new_intersection_ = Vec2(current_tile_.x + 1, m*(current_tile_.x + 1) + c);
    }
    else if (
        /* Bottom edge */
        (current_tile_.x - tolerance <= ((current_tile_.y - c)/m) && ((current_tile_.y - c)/m) <= (current_tile_.x + 1 + tolerance))
        && (direction_.y < 0)
    ){
        new_intersection_ = Vec2((current_tile_.y - c)/m, current_tile_.y);
    }
    else if (
        /* Bottom edge */
        (current_tile_.x - tolerance <= ((current_tile_.y + 1 - c)/m) && ((current_tile_.y + 1 - c)/m) <= (current_tile_.x + 1 + tolerance))
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

Vec2 LightSystem::ray_get_propogating_tile(Vec2 position, Vec2 direction){
    // This is because the just flooring that value isn't good enough.
    // It doesn't handle edge cases where the position is on the edge,
    // And the ray could be traveling either way.

    const double tolerance = 1e-6;
    Vec2 current_tile = Vec2::floor(position); // Could this give the wrong number on edge cases?
    if(direction.y < 0 && (
        position.y >= current_tile.y - tolerance && position.y <= current_tile.y + tolerance
    )){
        // If the ray is traveling left, and on the right edge, the current tile should move one left
        current_tile.y = current_tile.y - 1;
    }
    if(direction.x < 0 && (
        position.x > current_tile.x - tolerance && position.x < current_tile.x + tolerance
    )){
        // If the ray is traveling left, and on the right edge, the current tile should move one left
        current_tile.x = current_tile.x - 1;
    }
    return current_tile;
}


MColour LightSystem::get_light_at_distance(LightComponent &light, double distance){
    return (light.current_colour - MColour(static_cast<int>(255.0 * distance / light.range))).clamp();
}
