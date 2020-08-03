#pragma once

#include <vector>

#include "System.hpp"
#include "RenderSystem.hpp"

class Game;
class InputSystem : public System {

    RenderSystem m_pRender_system;
    std::vector<SDL_Event> m_last_events;

public:
    InputSystem(Game &game, RenderSystem &render_sytem);
    virtual void update(float dT) override;

};