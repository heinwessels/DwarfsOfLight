#pragma once

#include <list>

#include "System.hpp"

struct Node{
    Node *parent;
    double f;   // Total weight
    double g;   // Weight of distance from start to this
    double h;   // Weight of distance from this to goal
    int x, y;
    Node(Node *parent, int x, int y) : parent(parent), x(x), y(y) { }
    bool operator<(const Node& rhs) const{ return f < rhs.f; }
    bool operator==(const Node& rhs) const{ return x == rhs.x && y == rhs.y; }
};  // I want this private inside the class, but then the compiler complains (but it seems to work)

class Game;
class PathfindingSystem : public System {

public:
    PathfindingSystem(Game &game);
    virtual void init() override { };
    virtual void update(double dT) override;

private:

    bool astar_search(Vec2 start, Vec2 goal, std::list<Vec2> &path);
    void astar_backtrace_path(Node &end, std::list<Vec2> &path);
};