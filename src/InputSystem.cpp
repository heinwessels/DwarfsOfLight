#include "InputSystem.hpp"
#include "Game.hpp"
#include "Entity.hpp"

#include "RenderSystem.hpp"
#include "ControllerComponent.hpp"
#include "MoveComponent.hpp"

InputSystem::InputSystem(Game &game, RenderSystem &render_sytem)
    :   System(game, std::string("Input System")),
        m_pRender_system(render_sytem)
{
    m_signature |= Component::get_component_signature<ControllerComponent>();
    m_signature |= Component::get_component_signature<MoveComponent>();
}

void InputSystem::update(double dT){
    m_last_events = m_pRender_system.get_input_events();

    // Loop through all events
    for (auto &event : m_last_events){

        // First check if the game cares
        if (event.type == SDL_QUIT){
            m_pgame.quit();
        }

        // Handle the camera

        // Handle any movement controllers
        for(auto &entity : m_pgame.get_entities()){
            if(has_valid_signature(*entity)){

                // This entity should be moved by this controller
                MoveComponent &move = entity->get_component<MoveComponent>();
                ControllerComponent &controller = entity->get_component<ControllerComponent>();

                handle_entity_movement(event, move, controller);
            }
        }
    }
}


void InputSystem::handle_entity_movement(SDL_Event &event, MoveComponent &move, ControllerComponent &controller){

    Vec2 direction = {0.0};

    // Handle Up
    if (!controller.has_up_input && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP){
        direction.y += -1;
        controller.has_up_input = true;
    }
    else if (controller.has_up_input){
        if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP){
            controller.has_up_input = false;
        }
        else{
            direction.y += -1;
        }
    }

    // Handle Down
    if (!controller.has_down_input && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN){
        direction.y += 1;
        controller.has_down_input = true;
    }
    else if (controller.has_down_input){
        if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN){
            controller.has_down_input = false;
        }
        else{
            direction.y += 1;
        }
    }

    // Handle Left
    if (!controller.has_left_input && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT){
        direction.x += -1;
        controller.has_left_input = true;
    }
    else if (controller.has_left_input){
        if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFT){
            controller.has_left_input = false;
        }
        else{
            direction.x += -1;
        }
    }

    // Handle Right
    if (!controller.has_right_input && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT){
        direction.x += 1;
        controller.has_right_input = true;
    }
    else if (controller.has_right_input){
        if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RIGHT){
            controller.has_right_input = false;
        }
        else{
            direction.x += 1;
        }
    }

    // Now update target direction
    move.target_direction = direction * ((direction.x != 0 || direction.y != 0) ? 1 : 1.0/sqrt(2.0)); // Normalize
}