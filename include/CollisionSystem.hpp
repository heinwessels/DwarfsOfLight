#pragma once

#include "Vec2.hpp"
#include "System.hpp"

class Tile;
class CollisionBox;
class Game;
class CollisionSystem : public System {

public:
    CollisionSystem(Game &game);
    virtual void init() override { };
    virtual void update(double dT) override;

private:
    void check_collision_with_world();
    void check_collision_with_entities();

    bool repel_if_collision(Vec2 &a_pos, const CollisionBox &a_box, Vec2 &b, const CollisionBox &b_box);
    bool has_collision(const Vec2 a, const Vec2 a_size, const Vec2 b, const Vec2 b_size);
    Vec2 get_shortest_distance_resolve_conflict(const Vec2 a, const Vec2 a_size, const Vec2 b, const Vec2 b_size);
    Tile* get_closest_tile_in_range_with_collisionbox(Vec2 point, Vec2 range);
};