#include "RenderSystem.hpp"
#include "Game.hpp"

RenderSystem::RenderSystem(Game &game, int width, int height)
    : System(game), m_Renderer(width, height)
{
    m_signature |= Component::get_component_signature(MoveComponentID);
    m_signature |= Component::get_component_signature(RenderComponentID);
}

void RenderSystem::update(float dT){

    m_Renderer.clear_screen();

    for(auto const entity : m_pgame.m_entities){
        if(has_valid_signature(*entity)){

            Renderable &renderable = static_cast<Renderable&>(entity->get_component(RenderComponentID));
            MoveComponent &move = static_cast<MoveComponent&>(entity->get_component(MoveComponentID));

            m_Renderer.renderTextureToScreen(
                renderable.m_pTexture,
                (int)move.position.x, (int)move.position.y,
                (int)renderable.width, (int)renderable.height
            );

        }
    }

    m_Renderer.show_screen();
}