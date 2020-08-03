#include "InputSystem.hpp"
#include "Game.hpp"

InputSystem::InputSystem(Game &game, RenderSystem &render_sytem)
    :   System(game), m_pRender_system(render_sytem)
{
    m_signature |= Component::get_component_signature(ControllerComponentID);
}

void InputSystem::update(float dT){
    m_last_events = m_pRender_system.get_input_events();

    // Loop through all events
    for (auto &event : m_last_events){

        // First check if the game cares
        if (event.type == SDL_QUIT){
            m_pgame.quit();
        }
    }

}