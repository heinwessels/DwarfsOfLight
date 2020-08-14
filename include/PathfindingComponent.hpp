#pragma once

#include <list>

#include "Component.hpp"
#include "Vec2.hpp"

class PathfindingComponent : public Component{
    Vec2 m_target = {0};
    bool m_path_requested = false;
    bool m_move_to_target = false;
    std::list<Vec2> m_path;
public:
    PathfindingComponent () : Component(PathfindingComponentID) { }

    void go_to_target(Vec2 target){ m_target = target; m_path_requested = true; }
    Vec2 get_target() { return m_target;
    }
    bool is_path_requested() { return m_path_requested; }
    void set_path(std::list<Vec2> path) { m_path = path; m_path_requested = false; }

    void reached_target() { m_move_to_target = false; }
};