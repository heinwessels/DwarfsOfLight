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
            grow_light_source(lightmap, light, entity->get_posision());
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

void LightSystem::grow_light_source(LightMap &lightmap, LightComponent light, Vec2 origin){
    // The <lightmap> will contain the output data

    // Create the list of seeds that need to grow.
    std::list<Seed> seeds;
    Seed source_seed = Seed(floor(origin.x), floor(origin.y));
    seeds.push_front(source_seed);  // This guy will execute first

    // Also add the first 8 neighbours to ensure it grows in all directions
    seeds.push_front(Seed(source_seed.x + 1, source_seed.y + 1)); // Top row
    seeds.push_front(Seed(source_seed.x + 0, source_seed.y + 1));
    seeds.push_front(Seed(source_seed.x - 1, source_seed.y + 1));
    seeds.push_front(Seed(source_seed.x + 1, source_seed.y - 1)); // Bottom row
    seeds.push_front(Seed(source_seed.x + 0, source_seed.y - 1));
    seeds.push_front(Seed(source_seed.x - 1, source_seed.y - 1));
    seeds.push_front(Seed(source_seed.x - 1, source_seed.y));       // Left and right
    seeds.push_front(Seed(source_seed.x + 1, source_seed.y));

    // Sanity check to prevent infinite loops (WILL NEED IMPROVEMENT)
    int maximum_steps = ceil((light.max_dist+3)*(light.max_dist+3)*M_PI);
    int count_steps = 0;
    bool failed = false;

    while(!seeds.empty() && !failed){

        // Remove the front seed
        Seed seed = seeds.back();
        seeds.pop_back();

        // Add light at this seed
        lightmap.set_lighting_at(seed.x, seed.y, light.base_colour);
        lightmap.modify(seed.x, seed.y);    // This is still a hacky solution

        // Grow this seed to get more!
        if (m_pgame.get_world().get_tiles()[seed.x][seed.y].get_type() != Tile::TypeWall){
            // But only if this seed is NOT on a wall.
            // We still allow the wall, because we need to see it.

            std::list<Seed> new_seeds = grow_light_seed(seed, origin, lightmap, light);

            // Add these seeds to the master pile
            seeds.splice(seeds.begin(), new_seeds); // This will add new seeds at the front
        }


        // A sanity check to prevent infinite loops (TEMPORARY)
        if (count_steps++ > maximum_steps){
            failed = true;
            printf("ERROR: The light source growing failed!\n");
        }
    }

}

std::list<Seed> LightSystem::grow_light_seed(Seed source_seed, Vec2 origin, LightMap& lightmap, LightComponent light){
    using World = std::vector<std::vector<Tile>>;
    World &world = m_pgame.get_world().get_tiles();

    // Calculate angle from origin to the source seed
    float angle = atan2(source_seed.y - origin.y, source_seed.x - origin.x);
    // NOTE: If <atan2> takes too long, can change to using gradient. Just be careful of infinity.

    // First the source's three neighbours based on the angle to the origin
    std::list<Seed> possible_seeds = get_neighbour_seeds_in_direction(source_seed, angle);

    // Now loop through each seed and make sure it's a valid place to grow
    // And if it's valid, update the lightmap
    std::list<Seed> valid_seeds;
    for (auto & seed : possible_seeds){

        if (seed.x < 0 || seed.x > lightmap.get_width() || seed.y < 0 || seed.y > lightmap.get_height()){
            // This tile is out of bounds. Not valid!
        }
        else if (lightmap.has_been_modifed(seed.x, seed.y)){
            // This tile has already been grown to. Not valid
        }
        else if (light.max_dist < (seed.x-origin.x)*(seed.x-origin.x) + (seed.y-origin.y)*(seed.y-origin.y)){
            // The light doesn't shine this far
        }
        else{
            // This tile will get light! (I hope)
            valid_seeds.push_front(seed);
        }
    }


    return valid_seeds;
}

std::list<Seed> LightSystem::get_neighbour_seeds_in_direction(Seed seed, float angle){
    // Returns the 3 neighbours in the direction of the angle

    int angle_sign = angle > 0 ? 1 : -1;
    std::list<Seed> seeds;

    // Dividing the coordinate system into octants.
    if (abs(angle) < 22.5){
        seeds.push_front(Seed(seed.x + 1, seed.y + 1));
        seeds.push_front(Seed(seed.x + 1, seed.y));
        seeds.push_front(Seed(seed.x + 1, seed.y - 1));
    }
    else if (abs(angle) < 67.5){
        seeds.push_front(Seed(seed.x + 0, seed.y + angle_sign));
        seeds.push_front(Seed(seed.x + 1, seed.y + angle_sign));
        seeds.push_front(Seed(seed.x + 1, seed.y));
    }
    else if (abs(angle) < 112.5){
        seeds.push_front(Seed(seed.x - 1, seed.y + angle_sign));
        seeds.push_front(Seed(seed.x + 0, seed.y + angle_sign));
        seeds.push_front(Seed(seed.x + 1, seed.y + angle_sign));
    }
    else if (abs(angle) < 157.5){
        seeds.push_front(Seed(seed.x - 1, seed.y));
        seeds.push_front(Seed(seed.x - 1, seed.y + angle_sign));
        seeds.push_front(Seed(seed.x + 0, seed.y + angle_sign));
    }
    else /* abs(angle) > 157.5 */ {
        seeds.push_front(Seed(seed.x - 1, seed.y + 1));
        seeds.push_front(Seed(seed.x - 1, seed.y));
        seeds.push_front(Seed(seed.x - 1, seed.y - 1));
    }

    return seeds;
}