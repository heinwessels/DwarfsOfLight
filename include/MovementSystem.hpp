#pragma once

#include <vector>
#include "System.hpp"

class TransformComponent;
class MoveComponent;
class Game;
class MovementSystem : public System {

public:
    MovementSystem(Game &game);
    virtual void init() override { };
    virtual void update(double dT) override;

private:
    void handle_straight_movement(TransformComponent &transform, MoveComponent &move, double dT);
    void handle_sporadic_movement(TransformComponent &transform, MoveComponent &move, double dT);

    void catch_if_out_of_bounds(TransformComponent &transform);
};