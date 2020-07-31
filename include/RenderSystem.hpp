#pragma once

#include <stdio.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Game.hpp"
#include "Renderer.hpp"
#include "Entity.hpp"
#include "System.hpp"

class RenderSystem : public System{

    Renderer m_Renderer;

public:
    RenderSystem(Game &game, int width, int height);
    SDL_Texture* load_texture(std::string path){return m_Renderer.load_texture(path);}

    virtual void update(float dT) override;
};