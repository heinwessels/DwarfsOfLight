#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "Component.hpp"
#include "RenderSystem.hpp"

class Renderable : public Component{



public:
    SDL_Texture* m_pTexture = nullptr;
    Renderable (SDL_Texture* texture);
};