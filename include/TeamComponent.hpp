#pragma once

#include <vector>
#include "Component.hpp"

class TeamComponent : public Component{
public:
    static constexpr ComponentID ID = TeamComponentID;

    typedef int TeamID;
    TeamID my_team;

    std::vector<TeamID> flees_from;
    std::vector<TeamID> attacks;

    double vision_radius;
    double attack_strength; // damage per second

    TeamComponent(TeamID id, std::vector<TeamID> flees_from, std::vector<TeamID> attacks, double vision_radius, double attack_strength)
        :
        Component(ID),
        my_team(id),
        flees_from(flees_from), attacks(attacks),
        vision_radius(vision_radius), attack_strength(attack_strength)
        { }
};