#pragma once

#include "System.hpp"

class Game;
class AISystem : public System {

public:
    AISystem(Game &game);
    virtual void init() override { };
    virtual void update(double dT) override;

private:
    void handle_entity_ai(Entity& entity);
};