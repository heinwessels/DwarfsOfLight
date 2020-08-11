#pragma once

#include <vector>

#include "System.hpp"
#include "RenderSystem.hpp"
#include "MoveComponent.hpp"
#include "ControllerComponent.hpp"

class Game;
class InputSystem : public System {

    RenderSystem m_pRender_system;
    std::vector<SDL_Event> m_last_events;       // TODO: This breaks the "System has no state rule"

public:
    InputSystem(Game &game, RenderSystem &render_sytem);
    virtual void update(double dT) override;

private:
    void handle_entity_movement(SDL_Event &event, MoveComponent &move, ControllerComponent &controller);

};