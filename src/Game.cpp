#include "Game.hpp"

Game::Game()
    :   m_renderSystem(new RenderSystem(*this, screen_width, screen_height)),
        m_input_system(new InputSystem(*this, *m_renderSystem)),
        m_movementy_system(new MovementSystem(*this))
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
    m_renderSystem->update(dT);
    m_input_system->update(dT);
    m_movementy_system->update(dT);

    return m_state != e_quit;
}

void Game::init_systems(){

}