#include "Game.hpp"

Game::Game()
    : m_renderSystem(new RenderSystem(*this, screen_width, screen_height))
{
    m_entities.push_back(std::make_unique<Dwarf>(
        m_renderSystem->load_texture("textures/dwarf.png")
    ));
}


void Game::step(float dT){
    // Loop through all systems
}

void Game::init_systems(){

}