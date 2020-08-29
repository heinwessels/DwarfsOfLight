#include "CollisionSystem.hpp"
#include "Game.hpp"
#include "World.hpp"

#include "TransformComponent.hpp"
#include "CollisionBoxComponent.hpp"


CollisionSystem::CollisionSystem(Game &game)
    : System(game, std::string("Collision System"))
{
    m_signature |= Component::get_component_signature<TransformComponent>();
    m_signature |= Component::get_component_signature<CollisionBox>();
}

void CollisionSystem::update(double dT){
    check_collision_with_entities();
    check_collision_with_world();
};

void CollisionSystem::check_collision_with_world(){
    auto &entities = m_pgame.get_entities();
    for( auto entity = entities.begin(); entity != entities.end(); entity++ ){
        if(has_valid_signature(**entity)){
            // For each entity with a collision box

            TransformComponent &a_transform = (*entity)->get_component<TransformComponent>();;
            CollisionBox &a_box = (*entity)->get_component<CollisionBox>();;

            // Get the closest world tile with a collision component
            Tile *closest_tile = get_closest_tile_in_range_with_collisionbox(
                a_transform.position, Vec2(a_box.width, a_box.height)
            );
            if (closest_tile != nullptr){

                TransformComponent &tile_transform = closest_tile->get_component<TransformComponent>();;
                CollisionBox &tile_box = closest_tile->get_component<CollisionBox>();;

                repel_if_collision(
                    a_transform.position, a_box,
                    tile_transform.position, tile_box
                ); // The function itself will move the entity by reference (and not the tile)
            }
        }
    }
}

void CollisionSystem::check_collision_with_entities(){

    auto &entities = m_pgame.get_entities();
    for( auto a = entities.begin(); a != entities.end(); a++ ){
        if(has_valid_signature(**a)){
            for( auto b = a; b != entities.end(); b++ ){
                if(a != b && has_valid_signature(**b)){

                    TransformComponent &a_transform = (*a)->get_component<TransformComponent>();
                    TransformComponent &b_transform = (*b)->get_component<TransformComponent>();

                    CollisionBox &a_box = (*a)->get_component<CollisionBox>();
                    CollisionBox &b_box = (*b)->get_component<CollisionBox>();

                    repel_if_collision(
                        a_transform.position, a_box,
                        b_transform.position, b_box
                    );   // Positions are set inside this function
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
            double num_of_movers = !a_box.stationary + !b_box.stationary;
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


Tile* CollisionSystem::get_closest_tile_in_range_with_collisionbox(Vec2 point, Vec2 range){
    // <range> is size of square around <point>
    // Returns <nullptr> if none found.

    auto &world = m_pgame.get_world();
    auto &tiles = world.get_tiles();

    Tile* closest_tile = nullptr; // Empty tile
    double closest_distance_sq = 1e8;
    Vec2 bottom_left = point - range / 2;
    Vec2 top_right = point + range / 2;
    for (int x = floor(bottom_left.x); x <= ceil(top_right.x); x ++){
        for (int y = floor(bottom_left.y); y <= ceil(top_right.y); y ++){

            if (x >= 0 && x < world.get_width() && y >= 0 && y < world.get_height()){
                if(tiles[x][y].has_component<CollisionBox>()){

                    double dist_sq = Vec2::dist_sq(point, Vec2(x+0.5, y+0.5));

                    if(dist_sq < closest_distance_sq){
                        closest_distance_sq = dist_sq;
                        closest_tile = &tiles[x][y];
                    }
                }
            }
        }
    }

    return closest_tile;
}
