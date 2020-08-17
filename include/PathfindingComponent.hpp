#pragma once

#include <list>

#include "Component.hpp"
#include "Vec2.hpp"

class PathfindingComponent : public Component{
    Vec2 m_target = {0};
    bool m_path_requested = false;
    bool m_moving_to_target = false;
    std::list<Vec2> m_waypoints = {}; // Initialize to be empty

public:
    PathfindingComponent () : Component(PathfindingComponentID) { }

    void go_to_target(Vec2 target){ m_target = target; m_path_requested = true; }
    Vec2 get_target() { return m_target; }

    bool is_path_requested() { return m_path_requested; }
    void clear_pathing_request() { m_path_requested = false; }

    std::list<Vec2> &get_waypoints() { return m_waypoints; }

    void start_following_waypoints(){ m_moving_to_target = true; }
    bool is_moving_to_target(){ return m_moving_to_target; }
    void reached_target() { m_moving_to_target = false; }
};