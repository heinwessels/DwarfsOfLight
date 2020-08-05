#include "RenderSystem.hpp"
#include "InputSystem.hpp"
#include "MovementSystem.hpp"
#include "CollisionSystem.hpp"

#pragma once

#include <vector>

#include "Entity.hpp"
#include "World.hpp"

#include "Dwarf.hpp"
#include "Goblin.hpp"
#include "Tile.hpp"

class Game{
    // This is the main manager of the game.

    int screen_width = 1280, screen_height = 704;

    World m_world;
    std::vector<std::unique_ptr<System>> m_systems;
    std::vector<Entity*> m_entities;

    enum State {e_start, e_running, e_paused, e_quit};
    State m_state = e_start;

public:

    Game();
    ~Game();
    bool step(float dT);

    std::vector<Entity*> &get_entities() { return m_entities; }

    void quit(){m_state = e_quit;}

private:
    void init_systems();
};
