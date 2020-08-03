#include "RenderSystem.hpp"
#include "Game.hpp"

RenderSystem::RenderSystem(Game &game, int width, int height)
    : System(game), m_Renderer(width, height)
{
    m_signature |= Component::get_component_signature(RenderComponentID);
}

void RenderSystem::update(float dT){

    m_Renderer.clear_screen();

    for(auto const entity : game.m_entities){
        if(has_valid_signature(*entity)){

            Renderable &renderable = static_cast<Renderable&>(entity->get_component(RenderComponentID));

            m_Renderer.renderTextureToScreen(renderable.m_pTexture);

        }
    }

    m_Renderer.show_screen();
}