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
    Vec2 target_direction;    // [unit vector] The direction this entity should aim for
    double speed;

    // Type specific values
    struct {
        Vec2 current_direction = {0.707, 0.707};
        double rotation_speed = 0;
        double tightness_factor = 6;
        double period = 0.2;
        double time_to_change = 0;
    } sporadic;

    MoveComponent (Type type, double speed) : Component(ID), type(type), speed(speed) { }
};