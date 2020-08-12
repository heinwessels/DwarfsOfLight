#include "RenderSystem.hpp"
#include "InputSystem.hpp"
#include "MovementSystem.hpp"
#include "CollisionSystem.hpp"
#include "LightSystem.hpp"

#pragma once

#include <vector>

#include "Timing.hpp"
#include "Entity.hpp"
#include "World.hpp"

#include "Dwarf.hpp"
#include "Goblin.hpp"
#include "Tile.hpp"

class Game{
    // This is the main manager of the game.

    int screen_width = 1280, screen_height = 740;

    World m_world;
    std::vector<std::unique_ptr<System>> m_systems;
    std::vector<Entity*> m_entities;

    RenderSystem *m_rendersystem;   // We use this a lot, so keep reference to it

    enum State {e_start, e_running, e_paused, e_quit};
    State m_state = e_start;

public:

    Game();
    ~Game();
    bool update(double dT);

    std::vector<Entity*> &get_entities() { return m_entities; }
    World& get_world() {return m_world; }

    void quit(){m_state = e_quit;}

private:
    void load_systems();
    void init_systems();
};
