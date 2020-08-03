#include "RenderSystem.hpp"
#include "InputSystem.hpp"
#include "MovementSystem.hpp"

#pragma once

#include <vector>

#include "Entity.hpp"
#include "Dwarf.hpp"

class Game{
    // This is the main manager of the game.

    int screen_width = 1280, screen_height = 720;

    RenderSystem *m_renderSystem;    // TODO This should be part of some list
    InputSystem *m_input_system;
    MovementSystem *m_movementy_system;

    enum State {e_start, e_running, e_paused, e_quit};
    State m_state = e_start;

public:

    // Change this to something else
    std::vector<Entity*> m_entities;

    Game();
    ~Game();
    bool step(float dT);

    void quit(){m_state = e_quit;}

private:
    void init_systems();
};
