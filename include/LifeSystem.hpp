#pragma once

#include "System.hpp"
#include <memory>
#include <list>

class Vec2;
class LifeComponent;
class Game;
class LifeSystem : public System {

public:
    LifeSystem(Game &game);
    virtual void init() override { };
    virtual void update(double dT) override;

private:
    void handle_entity_life(Entity &entity, double dT);
    void attempt_reproduce(Entity &entity, double dT);
    int count_lifetype_in_list(std::list<Entity*> neighbours, LifeComponent& life);
    std::unique_ptr<Entity> create_offspring(LifeComponent& life, const Vec2& pos);
    Vec2 find_spot_to_reproduce(Vec2 position, Vec2 size, double maximum_range, std::list<Entity*> entities);
    Vec2 get_shortest_distance_resolve_conflict(const Vec2 a, const Vec2 a_size, const Vec2 b, const Vec2 b_size);
    bool has_collision(const Vec2 a, const Vec2 a_size, const Vec2 b, const Vec2 b_size);
};