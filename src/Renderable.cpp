#include "Renderable.hpp"

Renderable::Renderable (SDL_Texture* texture)
    : Component(RenderComponentID), m_pTexture (texture)
{

}

