#pragma once

#include <memory>
#include <vector>

class World;
class Entity;
class System;
class RenderSystem;
class Game{
    // This is the main manager of the game.

    int screen_width = 1280, screen_height = 740;

    std::unique_ptr<World> m_pWorld;
    std::vector<std::unique_ptr<System>> m_systems;
    std::vector<Entity*> m_entities;    // Why not unique pointer?

    RenderSystem *m_rendersystem;   // We use this a lot, so keep reference to it

    enum State {e_start, e_running, e_paused, e_quit};
    State m_state = e_start;

public:

    Game();
    ~Game();
    bool update(double dT);

    void add_entity(Entity* entity);

    std::vector<Entity*> &get_entities();
    World& get_world();
    RenderSystem& get_render_system();

    void quit();

private:
    void load_systems();
    void init_systems();
};
