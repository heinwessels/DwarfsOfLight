#include "Game.hpp"

#include "Dwarf.hpp"

Game::Game()
    : m_renderSystem(RenderSystem(screen_width, screen_height))
{
    m_gameObjects.push_back(std::make_unique<Dwarf>(
        0.0, 0.0,
        m_renderSystem.loadTexture("textures/dwarf.png")
    ));
}


void Game::step(float dT){



    // Last step is to render
    render();
}



void Game::render(){

    // Clear the screen
    m_renderSystem.clear_screen();

    // Draw all things
    for (auto & obj : m_gameObjects){
        m_renderSystem.renderTextureToScreen(obj->m_renderable->m_pTexture);
    }

    // Show the screen
    m_renderSystem.show_screen();
}