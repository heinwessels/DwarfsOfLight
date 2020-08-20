#pragma once

#include "Component.hpp"
#include "Vec2.hpp"

class TransformComponent : public Component{
public:
    static constexpr ComponentID ID = TransformComponentID;

    Vec2 position;
    Vec2 speed;
    TransformComponent (Vec2 position, Vec2 speed)
        : Component(ID), position(position), speed(speed) { }
    TransformComponent (Vec2 position) : TransformComponent(position, Vec2(0, 0)) { };
};