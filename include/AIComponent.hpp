#pragma once

#include "Component.hpp"
#include "Vec2.hpp"

class AIComponent : public Component{
public:
    static constexpr ComponentID ID = AIComponentID;

    typedef int Mode;
    static constexpr Mode ModeIdle = 0;
    static constexpr Mode ModeWandering = 1;
    static constexpr Mode ModeAttack = 2;
    static constexpr Mode ModeFlee = 4;
    static constexpr Mode ModeFindMate = 5;

    Mode mode;

public:
    AIComponent (Mode mode)
        : Component(ID), mode(mode)
        { }

    AIComponent () : AIComponent(ModeWandering) { }
};