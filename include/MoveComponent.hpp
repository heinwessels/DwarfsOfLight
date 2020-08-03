#pragma once

#include "Component.hpp"
#include "Vec2.hpp"

class MoveComponent : public Component{
public:
    Vec2 position = {0.0};
    Vec2 speed = {0.0};
    MoveComponent (Vec2 position, Vec2 speed) : Component(MoveComponentID), position(position), speed(speed) { }
};