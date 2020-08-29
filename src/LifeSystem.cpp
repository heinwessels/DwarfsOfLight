#include "LifeSystem.hpp"
#include "Game.hpp"
#include "World.hpp"

#include <stdio.h>
#include <vector>
#include <memory>

#include "RNG.hpp"
#include "Vec2.hpp"

#include "TransformComponent.hpp"
#include "LifeComponent.hpp"

#include "Mushroom.hpp"
#include "Firefly.hpp"
#include "Goblin.hpp"

LifeSystem::LifeSystem(Game& game)
    : System(game, std::string("Life System"))
{
    m_signature |= Component::get_component_signature<TransformComponent>();
    m_signature |= Component::get_component_signature<LifeComponent>();
}

void LifeSystem::update(double dT){
    for(auto const &entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){
            handle_entity_life(*entity, dT);
        }
    }
}

void LifeSystem::handle_entity_life(Entity &entity, double dT){

    auto &life = entity.get_component<LifeComponent>();


    // Handle food situation
    bool die_hunger = false;
    life.food -= life.food_consumption_rate * dT;
    if (life.food < 0){
        printf("%s died from hunger!\n", entity.get_name().c_str());
        die_hunger = true;
    }

    // Handle lifetime
    bool die_age = false;
    if (life.can_die_of_age){
        life.time_till_death -= dT;
        if(life.time_till_death < 0){
            printf("%s died from old age!\n", entity.get_name().c_str());
            die_age = true;
        }
    }

    // Handle health
    bool die_health = false;
    if(life.health < 0){
        printf("%s died from attack!\n", entity.get_name().c_str());
        die_health = true;
    }

    // Handle reproduction
    if (life.can_reproduce){
        attempt_reproduce(entity, dT);
    }

    // Should this entity die?
    if (
        die_hunger || die_age || die_health
    ){
        // Mark this entity to be killed.
        entity.kill();
    }
}

void LifeSystem::attempt_reproduce(Entity &entity, double dT){
    auto &life = entity.get_component<LifeComponent>();
    auto &world = m_pgame.get_world();

    // Are we ready?
    if (life.time_till_reproduce > 0){
        life.time_till_reproduce -= dT;
        if (life.time_till_reproduce < 0){
            life.ready_to_reproduce = true;
        }
    }

    // Can we reproduce now?
    if (life.ready_to_reproduce){
        bool can_reproduce = true;
        if (life.food < life.reproduce_minimum_food){
            // Are we too hungry?
            can_reproduce = false;
        }

        // Get the neighbours
        auto &transform = entity.get_component<TransformComponent>();
        std::list<Entity*> neighbours = world.get_occupancy_map().find_entities_in_range(
            world, transform.position, Vec2(3, 3)
        );  /// Counting in current tile, and all neighbouring tiles

        // Count the amount of neighbours of the same type of life
        int family = count_lifetype_in_list(neighbours, life);
        family -= 1;    // Don't count yourself

        if(life.need_mate_to_reproduce){
            // We need a mate. Are we close enough to reproduce?

            // TODO
            can_reproduce = false;
        }

        if (family >= life.max_neighbours_for_reproduction){
            // There is too much neighbours to reproduce
            can_reproduce = false;
        }

        if (can_reproduce){
            // We can reproduce! Woohoo.
            neighbours = world.get_occupancy_map().find_entities_in_range(
                world, transform.position, Vec2(5, 5)
            );  // Looking a little further for collisions
            Vec2 new_born_position = find_spot_to_reproduce(
                transform.position,
                Vec2(0.3, 0.3), // Size of entities (TODO Make configurable)
                2.5,
                neighbours
            );

            // Did we find a valid location?
            if (!isnan(new_born_position.x)){
                // Yes! Create the baby at that location! (There's no such thing as babies in this world)
                m_pgame.add_entity(create_offspring(life, new_born_position));
            }
            else{
                // This was an failed attempt
            }

            // Reset the timer
            life.time_till_reproduce = life.reproduce_every * random_float_in_range(0.8, 1.5);
            life.ready_to_reproduce = false;
        }
    }
}

int LifeSystem::count_lifetype_in_list(std::list<Entity*> neighbours, LifeComponent& life){
    // Count enities around <position> in a rectangle of size <range>
    int count = 0;

    for (const auto & stranger : neighbours){
        if(stranger->has_component<LifeComponent>()){
            auto& stranger_life = stranger->get_component<LifeComponent>();
            if(stranger_life.type == life.type){
                count++;
            }
        }
    }

    return count;
}

Vec2 LifeSystem::find_spot_to_reproduce(Vec2 position, Vec2 size, double maximum_range, std::list<Entity*> entities){
    // Iterate around <position> to for a open spot of <size>, up to a <maximum_range> away from  <position>
    // Returns (NAN, NAN) if no spot was found.

    const auto &world = m_pgame.get_world();
    int tries = 10;  // Amount of times we will try a new starting point
    bool found_valid = false;

    while(!found_valid && tries--){

        // Try a new location
        Vec2 new_position = position + Vec2(
            random_sign() * random_float_in_range(size.x, 3*size.x),
            random_sign() * random_float_in_range(size.y, 3*size.y)
        );

        int inner_tries = 3;
        while(inner_tries--){
            // Loop through entities, and see if there is a collision
            bool collision = false;
            for (const auto &entity : entities){
                if (entity->has_component<TransformComponent>()){
                    const auto &transform = entity->get_component<TransformComponent>();

                    // Find the shortest distance between two squares
                    if (has_collision(
                        new_position, size,
                        transform.position, size
                    )){
                        collision = true;   // Remember

                        // Now attempt to resolve this conflict.
                        Vec2 shortest_distance = get_shortest_distance_resolve_conflict(
                            new_position, size,
                            transform.position, size
                        );

                        // Try to resolve the conflict.
                        // TODO: I don't understand this problem well enough.
                        // There must be a better way!
                        if(shortest_distance.x < shortest_distance.y){
                            // We need to move x direction
                            position.x += shortest_distance.x * random_float_in_range(1, 1.3) * random_sign();
                        }
                        else{
                            // We need to move y direction
                            position.y += shortest_distance.y * random_float_in_range(1, 1.3) * random_sign();
                        }

                        // Stop the loop
                        break;
                    }
                }
            }

            // Was this position clear?
            if(!collision){

                if(!world.within_bounds(floor(new_position.x), floor(new_position.y))){
                    // We are outside world limits somehow.
                    inner_tries = 0;    // Start from a new location.
                }
                else if(world.get_tile_type_at(floor(new_position.x), floor(new_position.y)) == Tile::TypeWall){
                    // We reached a wall tile
                    inner_tries = 0;    // Start from a new location.
                }
                else if (Vec2::dist_sq(position, new_position) > maximum_range*maximum_range){
                    // Too far from center
                    // Stop inner loop. We need to try a new position
                    inner_tries = 0;
                }
                else{
                    // Return it quick! This spot is open and not too far away!
                    //              (Doesn't really need to be quick)

                    return new_position;
                }
            }
            // else
            //      <new_position> will have been shifted
        }
    }

    // We didn't find a valid spot
    return Vec2(NAN, NAN);
}

Vec2 LifeSystem::get_shortest_distance_resolve_conflict(
    const Vec2 a, const Vec2 a_size,
    const Vec2 b, const Vec2 b_size
){
    // Calculates the shortest distance to move to resolve collision
    // This is copy-and-pasted from CollisionSystem.
    Vec2 r = b - a;
    Vec2 u = {r.x > 0.0f ? 1.0f : -1.0f, r.y > 0.0f ? 1.0f : -1.0f};
    return (b - (u * b_size * 0.5f)) - (a + (u * a_size * 0.5f));
}

bool LifeSystem::has_collision(
    const Vec2 a, const Vec2 a_size,
    const Vec2 b, const Vec2 b_size
){
    // Returns true if the collision boxes overlap
    return  (a.x - a_size.x / 2 )   < (b.x + b_size.x / 2) &&
            (a.x + a_size.x / 2 )   > (b.x - b_size.x / 2) &&
            (a.y - a_size.y / 2 )   < (b.y + b_size.y / 2) &&
            (a.y + a_size.y / 2 )   > (b.y - b_size.y / 2);
}


std::unique_ptr<Entity> LifeSystem::create_offspring(LifeComponent& life, const Vec2& pos){
    switch (life.type)
    {
    case LifeComponent::TypeFungi:
        return std::make_unique<Mushroom>(pos.x, pos.y);
        break;
    case LifeComponent::TypeBug:
        return std::make_unique<Firefly>(pos.x, pos.y);
        break;
    case LifeComponent::TypeGoblin:
        return std::make_unique<Goblin>(pos.x, pos.y);
        break;
    default:
        break;
        raise;
    }

    return nullptr;
}