#include "PathfindingSystem.hpp"
#include "Game.hpp"

#include <queue>
#include <array>

#include "PathfindingComponent.hpp"

PathfindingSystem::PathfindingSystem(Game &game)
    :   System(game, std::string("Moving System"))
{
    m_signature |= Component::get_component_signature(PathfindingComponentID);
}

void PathfindingSystem::update(double dT){
    for(auto const entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){

            PathfindingComponent &move = static_cast<PathfindingComponent&>(entity->get_component(MoveComponentID));


        }
    }
}

bool PathfindingSystem::astar_search(Vec2 start_point, Vec2 goal_point, std::list<Vec2> &path){

    Node goal { nullptr, floor(goal.x), floor(goal.y)};

    std::list<Node> open_nodes;
    std::list<Node> closed_nodes;

    // Add the starting node
    open_nodes.push_back(Node(
        nullptr, floor(start_point.x), floor(start_point.y)
    ));

    // Loop through open nodes. If it runs out it means no path
    bool reached_goal = false;
    while(!open_nodes.empty()){

        // Find the node with the lowest <f>
        double lowest_f = INT_MAX;
        auto lowest_iter = open_nodes.begin(); // We're going to keep track of the iterator
        for (auto iter = open_nodes.begin(); iter != open_nodes.end(); iter++){
            if (iter->f < lowest_f){
                lowest_iter = iter;
                lowest_f = iter->f;
            }
        }
        Node parent = *lowest_iter;         // Get the parent
        open_nodes.erase(lowest_iter);      // Pop it from the queue (or list)


        // Create the 8 children
        const std::array<std::array<int, 2>, 8> dxdy {{
            {{0, -1}}, {{0, 1}}, {{-1, 0}}, {{1, 0}}, {{-1, -1}}, {{-1, 1}}, {{1, -1}}, {{1, 1}}
        }};
        for (auto set : dxdy){
            int dx = set[0], dy = set[1];

            // Create child
            Node child {&parent, dx, dy};

            // Have we reached the end?
            if (child == goal){
                // Yes! Success!

                // Calculate the path by following the genealogy
                astar_backtrace_path(child, path);

                // Stop the loop
                return true;
            }

            // Update the <g> weight
            child.g += parent.g + (abs(dx) || abs(dy) ? 1.0 : 1.414);

            // Update the <h> weight with hypotenuse approximation
            int dist_to_goal_x = goal.x - child.x;
            int dist_to_goal_y = goal.y - child.y;
            child.h = std::max(dist_to_goal_x, dist_to_goal_y)
                         + 3.0/7.0*std::min(dist_to_goal_x, dist_to_goal_y);

            // Update the final weight
            child.f = child.g + child.h;

            // Is this child already in the OPEN list with lower <f>?
            for (auto & node : open_nodes){
                if (child.x == node.x && child.y == node.y && child.f > node.f){
                    // This child is not valid! Skip it!
                    continue;
                }
            }

            // Is this child already in the CLOSE list with lower <f>?
            for (auto & node : closed_nodes){
                if (child.x == node.x && child.y == node.y && child.f > node.f){
                    // This child is not valid! Skip it!
                    continue;
                }
            }

            // TODOOOOOOOOOOOOOOOO Is this tile valid?


            // This child is valid. (It won't reach here if it isn't)
            // Add to open list
            open_nodes.emplace_front(child);
        }
    }

    // We didn't reach the goal
    return false;
}

void PathfindingSystem::astar_backtrace_path(Node &end, std::list<Vec2> &path){
    // Node *parent = end.parent;
    // while(){

    // }
}