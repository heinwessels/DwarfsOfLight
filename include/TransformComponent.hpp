#pragma once

#include "Component.hpp"
#include "Vec2.hpp"

class TransformComponent : public Component{
public:
    static constexpr ComponentID ID = TransformComponentID;

    Vec2 position;
    double rotation;
    TransformComponent (Vec2 position) : Component(ID), position(position) { };
};