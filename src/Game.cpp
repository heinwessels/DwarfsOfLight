#include "Game.hpp"

Game::Game()
    :   m_renderSystem(new RenderSystem(*this, screen_width, screen_height)),
        m_input_system(new InputSystem(*this, *m_renderSystem))
{

    m_entities.push_back(new Dwarf(
        m_renderSystem->load_texture("textures/dwarf.png"),
        500, 500
    ));
}

Game::~Game(){
    for (auto entity : m_entities){
        delete entity;
    }
}

bool Game::step(float dT){

    // Loop through all systems
    m_renderSystem->update(0);
    m_input_system->update(0);


    return m_state != e_quit;
}

void Game::init_systems(){

}