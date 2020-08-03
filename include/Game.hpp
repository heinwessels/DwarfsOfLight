#include "RenderSystem.hpp"

#pragma once

#include <vector>

#include "Entity.hpp"
#include "Dwarf.hpp"

class Game{
    // This is the main manager of the game.

    int screen_width = 1280, screen_height = 720;

    RenderSystem *m_renderSystem;    // TODO This should be part of some list

public:

    // Change this to something else
    std::vector<Entity*> m_entities;

    Game();
    void step(float dT);

private:
    void init_systems();
};
