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
    for(auto const entity : m_pgame.get_entities()){
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

        auto &transform = entity.get_component<TransformComponent>();

        if(life.need_mate_to_reproduce){
            // We need a mate. Are we close enough to reproduce?

            // TODO
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

Entity* LifeSystem::create_offspring(LifeComponent& life, const Vec2& pos){
    switch (life.type)
    {
    case LifeComponent::TypeFungi:
        return new Mushroom(pos.x, pos.y);
        break;

    default:
        break;
        raise;
    }

    return nullptr;
}