#pragma once

#include "Component.hpp"
#include "Vec2.hpp"

class MoveComponent : public Component{
public:
    static constexpr ComponentID ID = MoveComponentID;

    typedef int Type;
    static constexpr Type TypeStraight = 0;
    static constexpr Type TypeSporadic = 1;
    Type type;

    bool has_target = false;
    Vec2 target;    // The next point this entity should aim for
    double speed;

    struct sporadic{
        double tightness_factor;
    };

    MoveComponent (Type type) : Component(ID), type(type) { }
};