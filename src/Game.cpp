#include "Game.hpp"

#include "RenderSystem.hpp"
#include "InputSystem.hpp"
#include "MovementSystem.hpp"
#include "CollisionSystem.hpp"
#include "LightSystem.hpp"
#include "PathfindingSystem.hpp"
#include "AISystem.hpp"
#include "TeamSystem.hpp"
#include "LifeSystem.hpp"
#include "OccupancyMapSystem.hpp"

#include "Timing.hpp"
#include "World.hpp"

#include "Entity.hpp"
#include "Dwarf.hpp"
#include "Goblin.hpp"
#include "Tile.hpp"
#include "Firefly.hpp"
#include "Mushroom.hpp"

Game::Game(){

    srand(time(NULL));

    m_pWorld = std::make_unique<World>("maps/map_test_1.csv");
    // m_pWorld = std::make_unique<World>("maps/arena.csv");
    // m_pWorld = std::make_unique<World>("maps/arena_small.csv");

    printf("World loaded.\n");

    load_systems();
    printf("Systems loaded.\n");

    // THIS IS FOR TESTING
    ////////////////////////////////////////////////

    add_entity(std::make_unique<Dwarf>(m_pWorld->get_width()/2, m_pWorld->get_height()/2));
    TransformComponent &positional = m_entity_entry_queue.back()->get_component<TransformComponent>();
    m_rendersystem->set_camera_target(&positional.position);
    m_rendersystem->set_camera_zoom(40);
    // m_pWorld->set_global_lighting(MColour(50));

    int num_of_mushrooms = 10;
    int num_of_fireflys = 30;
    int num_of_goblins = 10;
    for (int i = 0; i < num_of_mushrooms + num_of_fireflys + num_of_goblins; i++){
        Vec2 position = {0};
        bool position_valid = false;
        while(!position_valid){
            position = Vec2(
                random_float_in_range(2, m_pWorld->get_width() - 3),
                random_float_in_range(2, m_pWorld->get_height() - 3)
            );
            if(
                m_pWorld->get_tile_type_at(floor(position.x), floor(position.y))
                == Tile::TypeFloor
            ){
                position_valid = true;
            }
        }
        if(i < num_of_mushrooms){
            add_entity(std::make_unique<Mushroom>(position.x, position.y));
        }
        else if (i < num_of_mushrooms + num_of_fireflys){
            add_entity(std::make_unique<Firefly>(position.x, position.y));
        }
        else{
            add_entity(std::make_unique<Goblin>(position.x, position.y));
        }
    }
    ////////////////////////////////////////////////

    init_systems();
    printf("Systems initialized.\n");
}

Game::~Game(){
    // Shouldn't have to delete anyting
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

    add_queued_entities_to_world();
    remove_dead_entities();

    return m_state != e_quit;   // This state can be changed by systems
}

void Game::load_systems(){
    // The order in which systems are added to this vector
    // will determine in which order they will execute

    m_systems.push_back(std::make_unique<OccupancySystem>(*this));
    m_systems.push_back(std::make_unique<LightSystem>(*this));
    m_systems.push_back(std::make_unique<RenderSystem>(*this, screen_width, screen_height));

    // We want a way to access the Render System directly
    m_rendersystem = static_cast<RenderSystem*>(m_systems.back().get());    // TODO This is hacky.

    m_systems.push_back(std::make_unique<InputSystem>(*this, *m_rendersystem));   // This requires the RenderSystem
    m_systems.push_back(std::make_unique<TeamSystem>(*this));
    m_systems.push_back(std::make_unique<LifeSystem>(*this));
    m_systems.push_back(std::make_unique<AISystem>(*this));
    m_systems.push_back(std::make_unique<PathfindingSystem>(*this));
    m_systems.push_back(std::make_unique<MovementSystem>(*this));
    m_systems.push_back(std::make_unique<CollisionSystem>(*this));

}

void Game::init_systems(){
    for (auto &system : m_systems){
        system->init();
    }
}

void Game::add_entity(std::unique_ptr<Entity> entity){
    if (entity)
        m_entity_entry_queue.push_back(std::move(entity));
}

void Game::add_queued_entities_to_world(){
    m_entities.splice(m_entities.end(), m_entity_entry_queue);
}

void Game::remove_dead_entities(){
    m_entities.remove_if([](std::unique_ptr<Entity> &entity){ return !entity->is_still_alive(); });
}