#pragma once

#include <vector>

#include "System.hpp"
#include "MoveComponent.hpp"

class Game;
class MovementSystem : public System {

public:
    MovementSystem(Game &game);
    virtual void init() override { };
    virtual void update(double dT) override;
};