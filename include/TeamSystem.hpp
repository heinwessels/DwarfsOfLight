#pragma once

#include <vector>
#include "System.hpp"

class TransformComponent;
class Game;
class TeamSystem : public System {

public:
    TeamSystem(Game &game);
    virtual void init() override { };
    virtual void update(double dT) override;

private:
    void handle_entity(Entity &entity, double dT);
};