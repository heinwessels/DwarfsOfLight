#pragma once

#include "Component.hpp"
#include "Vec2.hpp"

class TransformComponent : public Component{
public:
    Vec2 position;
    Vec2 speed;
    TransformComponent (Vec2 position, Vec2 speed)
        : Component(TransformComponentID), position(position), speed(speed) { }
    TransformComponent (Vec2 position) : TransformComponent(position, Vec2(0, 0)) { };
};