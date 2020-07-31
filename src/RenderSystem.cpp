#include "RenderSystem.hpp"


RenderSystem::RenderSystem(Game &game, int width, int height)
    : System(game), m_Renderer(width, height)
{

}

void RenderSystem::update(float dT){
    Entity& entity = m_pGame.get_last_entity();
}