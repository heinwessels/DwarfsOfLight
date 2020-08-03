#pragma once

#include <stdio.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "System.hpp"
#include "Renderer.hpp"
#include "Entity.hpp"

class Game;
class RenderSystem : public System{

    Renderer m_Renderer;

public:
    RenderSystem(Game &game, int width, int height);
    SDL_Texture* load_texture(std::string path){return m_Renderer.load_texture(path);}

    virtual void update(Game &game, float dT) override;
};

