#include "RenderSystem.hpp"
#include "Game.hpp"

RenderSystem::RenderSystem(Game &game, int width, int height)
    : System(game), m_Renderer(width, height)
{

}

void RenderSystem::update(Game &game, float dT){

}