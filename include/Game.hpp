#pragma once

#include <vector>

#include "GameObject.hpp"
#include "RenderSystem.hpp"


class Game{
    // This is the main manager of the game.

    int screen_width = 1280, screen_height = 720;

    RenderSystem m_renderSystem;

    std::vector<std::unique_ptr<GameObject>> m_gameObjects;

public:
    Game();
    void step(float dT);


    void render();
};