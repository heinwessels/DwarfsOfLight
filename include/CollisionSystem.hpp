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

    bool has_collision(Vec2 a, Vec2 a_size, Vec2 b, Vec2 b_size);
};