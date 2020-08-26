#include "LifeSystem.hpp"
#include "Game.hpp"
#include "World.hpp"

#include <vector>
#include <memory>

#include "RNG.hpp"
#include "Vec2.hpp"

#include "TransformComponent.hpp"
#include "LifeComponent.hpp"

#include "Mushroom.hpp"

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

    bool die = false;

    // Handle food situation
    life.food -= life.food_consumption_rate * dT;
    if (life.food < 0){
        die = true;
    }

    // Handle reproduction
    if (life.can_reproduce){
        attempt_reproduce(entity, dT);
    }
}

void LifeSystem::attempt_reproduce(Entity &entity, double dT){
    auto &life = entity.get_component<LifeComponent>();

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

        // Count the amount of neighbours of the same type of life
        auto &transform = entity.get_component<TransformComponent>();
        int neighbours = count_lifetype_in_range(life, transform.position, Vec2(3, 3));
        neighbours -= 1;    // Counting yourself as a neighbour during reproduction is cheating.

        if(life.need_mate_to_reproduce){
            // We need a mate. Are we close enough to reproduce?

            // TODO
            can_reproduce = false;
        }

        if (neighbours >= life.max_neighbours_for_reproduction){
            // There is too much neighbours to reproduce
            can_reproduce = false;
        }

        if (can_reproduce){
            // We can reproduce! Woohoo.
            m_pgame.add_entity(create_offspring(life,
                transform.position + Vec2(
                    random_sign() * random_float_in_range(0.1, 1),
                    random_sign() * random_float_in_range(0.1, 1)
                )
            ));

            // Reset the timer
            life.time_till_reproduce = life.reproduce_every * random_float_in_range(0.8, 1.5);
            life.ready_to_reproduce = false;
        }
    }
}

int LifeSystem::count_lifetype_in_range(LifeComponent& life, Vec2 position, Vec2 range){
    // Count enities around <position> in a rectangle of size <range>
    int count = 0;
    auto &map = m_pgame.get_world().get_occupancy_map().get_map();

    Vec2 lower_left = {
        std::min(0.0, floor(position.x - range.x/2.0)),
        std::min(0.0, floor(position.y - range.y/2.0))
    };
    Vec2 upper_right = {
        std::max(floor(position.x + range.x/2.0), (double) m_pgame.get_world().get_width()),
        std::max(floor(position.y + range.y/2.0), (double) m_pgame.get_world().get_height())
    };

    for (int x = lower_left.x; x < upper_right.x; x ++)
        for (int y = lower_left.y; y < upper_right.y; y ++){
            // For every tile in the map

            for (auto entity : map[x][y]){
                // For every entity on this tile

                if(entity->has_component<LifeComponent>()){
                    auto &other_life = entity->get_component<LifeComponent>();
                    if (other_life.type == life.type){
                        // If entity contains the life we are looking for

                        count++;
                    }
                }
            }
        }

    return count;
}

std::unique_ptr<Entity> LifeSystem::create_offspring(LifeComponent& life, const Vec2& pos){
    switch (life.type)
    {
    case LifeComponent::TypeFungi:
        return std::make_unique<Mushroom>(pos.x, pos.y);
        break;

    default:
        break;
        raise;
    }

    return nullptr;
}