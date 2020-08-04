#include "CollisionSystem.hpp"
#include "Game.hpp"

CollisionSystem::CollisionSystem(Game &game)
    : System(game)
{
    m_signature |= Component::get_component_signature(MoveComponentID);
    m_signature |= Component::get_component_signature(CollisionBoxComponentID);
}

void CollisionSystem::update(float dT){
    auto entities = m_pgame.get_entities();

    for( auto a = entities.begin(); a != entities.end()-1; a++ ){
        if(has_valid_signature(**a)){

            for( auto b = a + 1; b != entities.end(); b++ ){
                if(has_valid_signature(**b)){

                    MoveComponent &a_move = static_cast<MoveComponent&>((*a)->get_component(MoveComponentID));
                    MoveComponent &b_move = static_cast<MoveComponent&>((*b)->get_component(MoveComponentID));

                    CollisionBox &a_box = static_cast<CollisionBox&>((*a)->get_component(CollisionBoxComponentID));
                    CollisionBox &b_box = static_cast<CollisionBox&>((*b)->get_component(CollisionBoxComponentID));

                    if (!a_box.stationary || !b_box.stationary){
                        // Don't check collisions between two stationary objects

                        if (has_collision(
                            a_move.position, Vec2(a_box.width, a_box.height),
                            b_move.position, Vec2(b_box.width, b_box.height)
                        )){

                            // These two objects have collided. Now what?

                            printf("Collision!");

                        }
                    }
                }
            }
        }
    }
};


bool CollisionSystem::has_collision(Vec2 a, Vec2 a_size, Vec2 b, Vec2 b_size){
    return  (a.x - a_size.x / 2 )   < (b.x + b_size.x / 2) &&
            (a.x + a_size.x / 2 )   > (b.x - b_size.x / 2) &&
            (a.y - a_size.y / 2 )   < (b.y + b_size.y / 2) &&
            (a.y + a_size.y / 2 )   > (b.y - b_size.y / 2);
}