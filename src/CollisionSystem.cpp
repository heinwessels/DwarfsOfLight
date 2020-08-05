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

                    Vec2 a_pos = (*a)->get_posision();
                    Vec2 b_pos = (*b)->get_posision();

                    MoveComponent &a_move = static_cast<MoveComponent&>((*a)->get_component(MoveComponentID));
                    MoveComponent &b_move = static_cast<MoveComponent&>((*b)->get_component(MoveComponentID));

                    CollisionBox &a_box = static_cast<CollisionBox&>((*a)->get_component(CollisionBoxComponentID));
                    CollisionBox &b_box = static_cast<CollisionBox&>((*b)->get_component(CollisionBoxComponentID));

                    if (!a_box.stationary || !b_box.stationary){
                        // Don't check collisions between two stationary objects

                        if (has_collision(
                            a_pos, Vec2(a_box.width, a_box.height),
                            b_pos, Vec2(b_box.width, b_box.height)
                        )){

                            // These two objects have collided. Now what?


                            // Move the object (if it can) to resolve the collision
                            Vec2 delta = get_shortest_distance_resolve_conflict(
                                a_pos, Vec2(a_box.width, a_box.height),
                                b_pos, Vec2(b_box.width, b_box.height)
                            );
                            if (abs(delta.x) < abs(delta.y))  // Only offset in the shortest direction
                                {delta.y=0.0f;}
                            else
                                {delta.x=0.0f;}
                            float num_of_movers = !a_box.stationary + !b_box.stationary;
                            a_pos += delta / num_of_movers * !a_box.stationary;
                            b_pos -= delta / num_of_movers * !b_box.stationary;

                            // Save the updated posisions
                            (*a)->set_posision(a_pos);
                            (*b)->set_posision(b_pos);
                        }
                    }
                }
            }
        }
    }
};


bool CollisionSystem::has_collision(
    const Vec2 a, const Vec2 a_size,
    const Vec2 b, const Vec2 b_size
){
    // Returns true if the collision boxes overlap
    return  (a.x - a_size.x / 2 )   < (b.x + b_size.x / 2) &&
            (a.x + a_size.x / 2 )   > (b.x - b_size.x / 2) &&
            (a.y - a_size.y / 2 )   < (b.y + b_size.y / 2) &&
            (a.y + a_size.y / 2 )   > (b.y - b_size.y / 2);
}

Vec2 CollisionSystem::get_shortest_distance_resolve_conflict(
    const Vec2 a, const Vec2 a_size,
    const Vec2 b, const Vec2 b_size
){
    // Calculates the shortest distance to move to resolve collision

    Vec2 r = b - a;
    Vec2 u = {r.x > 0.0f ? 1.0f : -1.0f, r.y > 0.0f ? 1.0f : -1.0f};
    return (b - (u * b_size * 0.5f)) - (a + (u * a_size * 0.5f));
}