#pragma once

#include "Component.hpp"
#include "Vec2.hpp"

class CollisionBox : public Component{
public:
    float width = 0, height = 0;

    bool stationary = false;
    bool die_on_collision = false;


    CollisionBox (float width, float height) : Component(CollisionBoxComponentID), width(width), height(height) { }
    CollisionBox (float width, float height, bool die_on_collision, bool stationary)
        : Component(CollisionBoxComponentID), width(width), height(height),
        stationary(stationary), die_on_collision(die_on_collision) { }
};