#pragma once

#include "Component.hpp"
#include "Vec2.hpp"

class AIComponent : public Component{
public:
    static constexpr ComponentID ID = AIComponentID;

    typedef int Mode;
    static constexpr Mode ModeIdle = 0;
    static constexpr Mode ModeWandering = 1;
    static constexpr Mode ModeFight = 2;
    static constexpr Mode ModeGraze = 3;
    static constexpr Mode ModeFlee = 4;

    Mode mode;

    bool can_graze;
    bool can_fight;

public:
    AIComponent (Mode mode, bool can_graze, bool can_fight)
        : Component(ID), mode(mode),
        can_graze(can_graze), can_fight(can_fight)
        { }

    AIComponent () : AIComponent(ModeWandering, false, false) { }
};