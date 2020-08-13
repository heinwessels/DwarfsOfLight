#include "Game.hpp"

Game::Game()
    : m_world (40, 22)
{

    m_world.load_world("maps/map_test_1.csv");
    // m_world.load_world("maps/empty_world.csv");

    printf("World loaded.\n");

    load_systems();
    printf("Systems loaded.\n");

    // THIS IS FOR TESTING
    ////////////////////////////////////////////////
    m_entities.push_back(new Dwarf(5, 9));
    m_rendersystem->set_camera_target(m_entities[0]->get_position_ptr());
    m_rendersystem->set_camera_zoom(40);
    m_entities.push_back(new Goblin(20, 9));
    ////////////////////////////////////////////////

    init_systems();
    printf("Systems initialized.\n");
}

Game::~Game(){
    for (auto entity : m_entities){
        delete entity;
    }
}

bool Game::update(double dT){

    // TODO: This should be `auto const`, but Inputsystem has a state that changes. Change!
    for (auto &system : m_systems){
        system->update_timed(dT); // <update_timed> internally measures the update time
    }

    // THIS IS HACKY TO SEE TIMINGS
    //////////////////////////////////////////////////////////////////
    static int count = 0;
    if (++count > 200){
        printf("-----------------------------------------------\n");
        printf("Timing Information (last, min, max) [ms]:\n");
        for (auto &system : m_systems){
            Timing timing = system->get_timing();
            printf("%20s:\t", system->get_name().c_str());
            printf("%5.3f\t%5.3f\t%5.3f\n",
                timing.get_update_time(),
                timing.get_update_time_min(),
                timing.get_update_time_max()
            );
        }
        count = 0;
    }
    //////////////////////////////////////////////////////////////////

    return m_state != e_quit;   // This state can be changed by systems
}

void Game::load_systems(){
    // The order in which systems are added to this vector
    // will determine in which order they will execute

    m_systems.push_back(std::make_unique<LightSystem>(*this));
    m_systems.push_back(std::make_unique<RenderSystem>(*this, screen_width, screen_height));

    // We want a way to access the Render System directly
    m_rendersystem = static_cast<RenderSystem*>(m_systems[1].get());    // TODO This is hacky.

    m_systems.push_back(std::make_unique<InputSystem>(*this, *m_rendersystem));   // This requires the RenderSystem
    m_systems.push_back(std::make_unique<MovementSystem>(*this));
    m_systems.push_back(std::make_unique<CollisionSystem>(*this));
}

void Game::init_systems(){
    for (auto &system : m_systems){
        system->init();
    }
}