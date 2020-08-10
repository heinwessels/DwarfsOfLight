#pragma once

#include <vector>

#include "System.hpp"
#include "MoveComponent.hpp"

class Game;
class MovementSystem : public System {

public:
    MovementSystem(Game &game);
    virtual void internal_update(float dT) override;
};