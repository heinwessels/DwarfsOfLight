#include "Renderable.hpp"

Renderable::Renderable (SDL_Texture* texture, float width, float height)
    :   Component(RenderComponentID), m_pTexture (texture),
        width(width), height(height)
{

}

