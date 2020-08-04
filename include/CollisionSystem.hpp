#pragma once

#include <vector>
#include <stdio.h>

#include "Vec2.hpp"

#include "System.hpp"
#include "CollisionSystem.hpp"

#include "MoveComponent.hpp"
#include "CollisionBoxComponent.hpp"

class Game;
class CollisionSystem : public System {

public:
    CollisionSystem(Game &game);
    virtual void update(float dT) override;

    bool has_collision(const Vec2 a, const Vec2 a_size, const Vec2 b, const Vec2 b_size);
    Vec2 get_shortest_distance_resolve_conflict(const Vec2 a, const Vec2 a_size, const Vec2 b, const Vec2 b_size);
};