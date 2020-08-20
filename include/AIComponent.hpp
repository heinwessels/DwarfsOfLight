#pragma once

#include "Component.hpp"
#include "Vec2.hpp"

class AIComponent : public Component{
public:
    static constexpr ComponentID ID = AIComponentID;

    typedef int Mode;
    static constexpr Mode ModeIdle = 0;
    static constexpr Mode ModeWandering = 1;

    double wondering_speed = 5;

private:
    Mode m_mode;

public:
    AIComponent (Mode mode) : Component(ID), m_mode(mode) { }

    Mode get_mode(){ return m_mode; }
};