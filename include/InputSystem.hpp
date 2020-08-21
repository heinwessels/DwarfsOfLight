#pragma once
#include "System.hpp"
#include "SDL2/SDL_events.h"

#include <vector>

class MoveComponent;
class ControllerComponent;
class RenderSystem;
class Game;
class InputSystem : public System {

    RenderSystem &m_pRender_system;
    std::vector<SDL_Event> m_last_events;       // TODO: This breaks the "System has no state rule"

public:
    InputSystem(Game &game, RenderSystem &render_sytem);
    virtual void init() override { };
    virtual void update(double dT) override;

private:
    void handle_entity_movement(SDL_Event &event, MoveComponent &move, ControllerComponent &controller);
};