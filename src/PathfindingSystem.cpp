// #define DBG_SHOW_PATHFINDING_COLOURS

#include "PathfindingSystem.hpp"
#include "Game.hpp"

#include <queue>

#include "TransformComponent.hpp"
#include "PathfindingComponent.hpp"

PathfindingSystem::PathfindingSystem(Game &game)
    :   System(game, std::string("Pathfinding System"))
{
    m_signature |= Component::get_component_signature(TransformComponentID);
    m_signature |= Component::get_component_signature(PathfindingComponentID);
}

void PathfindingSystem::update(double dT){
    for(auto const entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){

            TransformComponent &transform = static_cast<TransformComponent&>(entity->get_component(TransformComponentID));
            PathfindingComponent &pathfinding = static_cast<PathfindingComponent&>(entity->get_component(PathfindingComponentID));

            if (pathfinding.is_path_requested()){
                handle_pathfinding(transform, pathfinding);
            }
            if (pathfinding.is_moving_to_target()){
                handle_waypoint(transform, pathfinding);
            }
        }
    }
}

void PathfindingSystem::handle_waypoint(TransformComponent &transform, PathfindingComponent &pathfinding){

    // This is the next point we are aiming for
    Vec2 next_waypoint = pathfinding.get_waypoints().front();

    // How far are we from there
    Vec2 distance_to_target = next_waypoint - transform.position;

    // Are within half a unit of the goal?
    if(distance_to_target.x*distance_to_target.x + distance_to_target.y*distance_to_target.y < 0.5*0.5){
        // We've reached this waypoint

        // Remove this waypoint
        pathfinding.get_waypoints().pop_front();

        // If there's another one, follow. If not, stop moving
        if (pathfinding.get_waypoints().empty()){
            // We reached the target
            pathfinding.reached_target();

            // Stop this function
            return;
        }
        else{
            // Point towards the next one

            next_waypoint = pathfinding.get_waypoints().front();
        }
    }

    // If we reach here we need to move to the next waypoint
    Vec2 direction = (next_waypoint - transform.position);
    direction /= sqrt(direction.x*direction.x + direction.y*direction.y);
    transform.speed = direction * 1;    // Hardcoded speed
}

void PathfindingSystem::handle_pathfinding(TransformComponent &transform, PathfindingComponent &pathfinding){
    // Return if true if a pathfinding calculation was done so that the caller can count it

    // Attempt pathfinding
    if(astar_search(
        transform.position,
        pathfinding.get_target(),
        pathfinding.get_waypoints()
    ))  // This will set the path
    {
        // If it was successful. Follow them!
        pathfinding.start_following_waypoints();
    }

    // Send the path to the component
    // If it was unsuccessful, it will only clear the request
    pathfinding.clear_pathing_request();
}

bool PathfindingSystem::astar_search(Vec2 start_point, Vec2 goal_point, std::list<Vec2> &waypoints){

    waypoints.clear();   // Make sure there's nothing in here

    auto &world = m_pgame.get_world().get_tiles();

    Node goal { nullptr,
        static_cast<int>(floor(goal_point.x)),
        static_cast<int>(floor(goal_point.y))
    };
    if (world[goal.x][goal.y].get_type() == Tile::TypeWall){
        // This goal is inside a wall. Won't work.
        return false;
    }

    std::list<std::unique_ptr<Node>> open_nodes;
    std::list<std::unique_ptr<Node>> closed_nodes;

    // Add the starting node
    open_nodes.push_back(std::make_unique<Node>(
        nullptr, floor(start_point.x), floor(start_point.y)
    ));

    // Loop through open nodes. If it runs out it means no path
    while(!open_nodes.empty()){

        // Find the node with the lowest <f>
        double lowest_f = INT_MAX;
        auto lowest_iter = open_nodes.begin(); // We're going to keep track of the iterator
        for (auto iter = open_nodes.begin(); iter != open_nodes.end(); iter++){
            if ((*iter)->f < lowest_f){
                lowest_iter = iter;
                lowest_f = (*iter)->f;
            }
        }
        std::unique_ptr<Node> parent = std::move(*lowest_iter);         // Get the parent
        open_nodes.erase(lowest_iter);          // Pop it from the queue (or list)

        // Create the 8 children
        const std::array<std::array<int, 2>, 8> dxdy {{
            {{0, -1}}, {{0, 1}}, {{-1, 0}}, {{1, 0}}, {{-1, -1}}, {{-1, 1}}, {{1, -1}}, {{1, 1}}
        }};
        for (auto set : dxdy){
            int dx = set[0], dy = set[1];

            // Create child
            // We can can it as a temporary here. We will add it to <all_nodes>
            // soon, and only after might it's address be required.
            std::unique_ptr<Node> child = std::make_unique<Node>(
                 parent.get(), parent->x + dx, parent->y + dy
            );

            // Have we reached the end?
            if (*child == goal){
                // Yes! Success!

                // Calculate the path by following the genealogy
                astar_backtrace_path(*child, waypoints);
                waypoints.push_back(goal_point);    // The final little step

                // Stop the loop
                return true;
            }

            // Is this child inside a wall?
            if (world[child->x][child->y].get_type() == Tile::TypeWall){
                // Yup. It's not valid.
                continue;
            }

            // Update the <g> weight
            child->g = parent->g + (abs(dx) || abs(dy) ? 1.0 : 2.0);   // The square distance

            // Update the <h> weight with hypotenuse approximation
            int dist_to_goal_x = goal.x - child->x;
            int dist_to_goal_y = goal.y - child->y;
            child->h = dist_to_goal_x*dist_to_goal_x + dist_to_goal_y*dist_to_goal_y;    // Square distance

            // Update the final weight
            child->f = child->g + child->h;

            // Is this child already in the OPEN list with lower <f>?
            bool valid = true;
            for (auto & node : open_nodes){
                if (child->x == node->x && child->y == node->y && child->f > node->f){
                    // This child is not valid! Skip it!
                    valid = false;
                    continue;
                }
            }
            if (!valid){
                // Skip the rest of this loop iteration.
                continue;
            }

            // Is this child already in the CLOSE list with lower <f>?
            valid = true;
            for (auto & node : closed_nodes){
                if (child->x == node->x && child->y == node->y && child->f > node->f){
                    // This child has already been tried! Skip it!
                    valid = false;
                    continue;
                }
            }
            if (!valid){
                // Skip the rest of this loop iteration.
                continue;
            }

            // This child is valid. (It won't reach here if it isn't)
            // Add to open list
#ifdef DBG_SHOW_PATHFINDING_COLOURS
            Renderable &renderable = static_cast<Renderable&>(world[child->x][child->y].get_component(RenderComponentID));
            renderable.set_colour_mod(MColour(0, 255, 0));
#endif
            open_nodes.push_front(std::move(child));
        }

        // Add this current parent to the closed list so we don't check it again
        // <std::move> will keep the parent at the same address and only move the pointer,
        // which means the child's <parent> will still be valid.
#ifdef DBG_SHOW_PATHFINDING_COLOURS
        Renderable &renderable = static_cast<Renderable&>(world[parent->x][parent->y].get_component(RenderComponentID));
        renderable.set_colour_mod(MColour(255, 0, 0));
        // m_pgame.get_render_system().update(0);  // Force update (Can be commented out)
#endif
        closed_nodes.push_front(std::move(parent));
    }

    // We didn't reach the goal
    return false;
}

void PathfindingSystem::astar_backtrace_path(Node &end, std::list<Vec2> &waypoints){

    // Find the best path by following the end-node's parents
    Node *node = &end;
    while (node != nullptr){
        waypoints.push_front(Vec2(
            node->x + 0.5,
            node->y + 0.5
        )); // Index point to the corner of tile, but want to move through the middle

#ifdef DBG_SHOW_PATHFINDING_COLOURS
        Renderable &renderable = static_cast<Renderable&>(m_pgame.get_world().get_tiles()[node->x][node->y].get_component(RenderComponentID));
        renderable.set_colour_mod(MColour(0, 0, 255));
#endif
        node = node->parent;
    }
}