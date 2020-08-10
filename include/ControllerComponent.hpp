#pragma once

#include "Component.hpp"
#include "Vec2.hpp"

class ControllerComponent : public Component{
public:
    double max_speed = 1;                   // In pixels per second
    bool    has_up_input = false,
            has_down_input = false,
            has_left_input = false,
            has_right_input = false;        // This is for smooth movement (TODO Just get keyboard STATE as well)

    ControllerComponent (double max_speed) : Component(ControllerComponentID), max_speed(max_speed) { }
};