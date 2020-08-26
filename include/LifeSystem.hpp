#pragma once

#include "System.hpp"

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
    Entity* create_offspring(LifeComponent& life, const Vec2& pos);
};