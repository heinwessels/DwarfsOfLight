#include "Game.hpp"

Game::Game()
    : m_renderSystem(new RenderSystem(*this, screen_width, screen_height))
{

    m_entities.push_back(new Dwarf(
        m_renderSystem->load_texture("textures/dwarf.png"),
        500, 500
    ));
}


void Game::step(float dT){
    // Loop through all systems
    m_renderSystem->update(0);
}

void Game::init_systems(){

}