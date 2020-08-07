#include "CollisionSystem.hpp"
#include "Game.hpp"

CollisionSystem::CollisionSystem(Game &game)
    : System(game)
{
    m_signature |= Component::get_component_signature(CollisionBoxComponentID);
}

void CollisionSystem::update(float dT){
    check_collision_with_entities();
    check_collision_with_world();
};


void CollisionSystem::check_collision_with_world(){
    auto entities = m_pgame.get_entities();
    for( auto entity = entities.begin(); entity != entities.end(); entity++ ){
        if(has_valid_signature(**entity)){
            // For each entity with a collision box

            Vec2 a_pos = (*entity)->get_posision();
            CollisionBox &a_box = static_cast<CollisionBox&>((*entity)->get_component(CollisionBoxComponentID));

            // Get the closest world tile with a collision component
            Tile *closest_tile = m_pgame.get_world().get_closest_tile_in_range_with_component(
                a_pos, Vec2(a_box.width, a_box.height), CollisionBoxComponentID
            );
            if (closest_tile != nullptr){

                Vec2 tile_pos = closest_tile->get_posision();
                CollisionBox &tile_box = static_cast<CollisionBox&>(closest_tile->get_component(CollisionBoxComponentID));

                if(repel_if_collision(
                    a_pos, a_box,
                    tile_pos, tile_box
                )){
                    (*entity)->set_posision(a_pos);
                    // Not possible for tile to move (repel will account for this)
                }
            }
        }
    }
}

void CollisionSystem::check_collision_with_entities(){
    auto entities = m_pgame.get_entities();
    for( auto a = entities.begin(); a != entities.end()-1; a++ ){
        if(has_valid_signature(**a)){

            for( auto b = a + 1; b != entities.end(); b++ ){
                if(has_valid_signature(**b)){

                    Vec2 a_pos = (*a)->get_posision();
                    Vec2 b_pos = (*b)->get_posision();

                    CollisionBox &a_box = static_cast<CollisionBox&>((*a)->get_component(CollisionBoxComponentID));
                    CollisionBox &b_box = static_cast<CollisionBox&>((*b)->get_component(CollisionBoxComponentID));

                    if(repel_if_collision(
                        a_pos, a_box,
                        b_pos, b_box
                    )){
                        (*a)->set_posision(a_pos);
                        (*b)->set_posision(b_pos);
                    }
                }
            }
        }
    }
}

bool CollisionSystem::repel_if_collision(
    Vec2 &a_pos, const CollisionBox &a_box,
    Vec2 &b_pos, const CollisionBox &b_box
){
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

            return true;
        }
    }

    return false;
}

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