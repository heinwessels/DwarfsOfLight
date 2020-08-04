#include "RenderSystem.hpp"
#include "InputSystem.hpp"
#include "MovementSystem.hpp"
#include "CollisionSystem.hpp"

#pragma once

#include <vector>

#include "Entity.hpp"

#include "Dwarf.hpp"
#include "Goblin.hpp"

class Game{
    // This is the main manager of the game.

    int screen_width = 1280, screen_height = 720;

    std::vector<std::unique_ptr<System>> m_systems;

    enum State {e_start, e_running, e_paused, e_quit};
    State m_state = e_start;

public:

    // Change this to something else
    std::vector<Entity*> m_entities;

    Game();
    ~Game();
    bool step(float dT);

    std::vector<Entity*> &get_entities() { return m_entities; }

    void quit(){m_state = e_quit;}

private:
    void init_systems();
};
