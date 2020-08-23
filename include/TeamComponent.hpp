#pragma once

#include <vector>
#include "Component.hpp"
#include "Vec2.hpp"

class TeamComponent : public Component{
public:
    static constexpr ComponentID ID = TeamComponentID;

    typedef int TeamID;
    TeamID team;

    std::vector<TeamID> flees_from;
    std::vector<TeamID> attacks;

    double vision_radius = 10;
    double attack_radius = 3;

    double attack_strength; // damage per second
    bool prefer_flee_not_attack = true;

    // Keep track of closest enemy to flee from that's visible
    bool enemy_close = false;
    Vec2 enemy_close_dir = Vec2(0);

    // Keep track of closest enemy to attack from that's visible
    bool foe_close = false;
    Vec2 foe_close_dir = Vec2(0);

    TeamComponent(TeamID team, std::vector<TeamID> flees_from, std::vector<TeamID> attacks, double attack_strength)
        :
        Component(ID),
        team(team),
        flees_from(flees_from), attacks(attacks),
        attack_strength(attack_strength)
        { }

    TeamComponent(TeamID team, double attack_strength)
        : TeamComponent(
            team,
            std::vector<TeamComponent::TeamID>({}),
            std::vector<TeamComponent::TeamID>({}),
            attack_strength
        ) { }
};