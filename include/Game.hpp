#pragma once

#include <memory>
#include <vector>
#include <list>

class World;
class Entity;
class System;
class RenderSystem;
class Game{
    // This is the main manager of the game.

    int screen_width = 1280, screen_height = 740;

    std::unique_ptr<World> m_pWorld;
    std::vector<std::unique_ptr<System>> m_systems;
    std::list<std::unique_ptr<Entity>> m_entities;
    std::list<std::unique_ptr<Entity>> m_entity_entry_queue; // Temporarily store new entities added during update

    RenderSystem *m_rendersystem;   // We use this a lot, so keep reference to it

    enum State {e_start, e_running, e_paused, e_quit};
    State m_state = e_start;

public:

    Game();
    ~Game();
    bool update(double dT);

    void add_entity(std::unique_ptr<Entity> entity);

    std::list<std::unique_ptr<Entity>> &get_entities(){ return m_entities; };
    World& get_world() { return *m_pWorld; }
    void quit(){ m_state = e_quit; }
    RenderSystem& get_render_system() { return *m_rendersystem; /* For debugging */}

private:
    void load_systems();
    void init_systems();

    void add_queued_entities_to_world();
};
