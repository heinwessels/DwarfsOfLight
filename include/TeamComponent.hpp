#pragma once

#include <vector>
#include "Component.hpp"
#include "Vec2.hpp"

class TeamComponent : public Component{
public:
    static constexpr ComponentID ID = TeamComponentID;

    typedef int TeamID;
    TeamID team;

    // Keep track of closest enemy to flee from that's visible
    std::vector<TeamID> flees_from;
    bool enemy_flee_close = false;
    Vec2 enemy_flee_dir = Vec2(0);

    // Keep track of closest enemy to attack from that's visible
    std::vector<TeamID> attacks;
    bool enemy_attack_close = false;
    Vec2 enemy_attack_dir = Vec2(0);

    double vision_radius = 5;
    double attack_radius = 1;

    double attack_strength; // damage per second


    TeamComponent(TeamID team, std::vector<TeamID> flees_from, std::vector<TeamID> attacks, double attack_strength, double vision_radius)
        :
        Component(ID),
        team(team),
        flees_from(flees_from), attacks(attacks),
        vision_radius(vision_radius),
        attack_strength(attack_strength)
        { }

    TeamComponent(TeamID team)
        : TeamComponent(
            team,
            std::vector<TeamComponent::TeamID>({}),
            std::vector<TeamComponent::TeamID>({}),
            0, 0
        ) { }
};