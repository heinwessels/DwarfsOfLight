#pragma once

#include "Component.hpp"

#include <list>
#include "Vec2.hpp"

class PathfindingComponent : public Component{
public:
    static constexpr ComponentID ID = PathfindingComponentID;

    Vec2 target = {0};
    bool path_requested = false;
    bool moving_to_target = false;
    std::list<Vec2> waypoints = {}; // Initialize to be empty

    PathfindingComponent () : Component(ID) { }
};