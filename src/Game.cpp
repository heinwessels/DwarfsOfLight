#include "Game.hpp"

Game::Game()
    : m_world (40, 22)
{

    init_systems();


    // THIS IS FOR TESTING
    ////////////////////////////////////////////////
    m_entities.push_back(new Dwarf(10, 10));
    m_entities.push_back(new Goblin(10, 8));
    ////////////////////////////////////////////////
}

Game::~Game(){
    for (auto entity : m_entities){
        delete entity;
    }
}

bool Game::step(float dT){

    // TODO: This should be `auto const`, but Inputsystem has a state that changes. Change!
    for (auto &system : m_systems){
        system->update(dT);
    }

    return m_state != e_quit;
}

void Game::init_systems(){
    // The order in which systems are added to this vector
    // will determine in which order they will execute

    m_systems.push_back(std::make_unique<LightSystem>(*this));
    m_systems.push_back(std::make_unique<RenderSystem>(*this, screen_width, screen_height));
    m_systems.push_back(std::make_unique<InputSystem>(*this, *static_cast<RenderSystem*>(m_systems[0].get())));   // This requires the RenderSystem
    m_systems.push_back(std::make_unique<MovementSystem>(*this));
    m_systems.push_back(std::make_unique<CollisionSystem>(*this));
}