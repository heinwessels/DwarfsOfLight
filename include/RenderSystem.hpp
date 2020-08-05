#pragma once

#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "System.hpp"
#include "Renderer.hpp"
#include "Entity.hpp"
#include "Renderable.hpp"

class Game;
class RenderSystem : public System{

    Renderer m_Renderer;

public:
    RenderSystem(Game &game, int width, int height);
    void load_texture_if_not_loaded(Renderable &renderable);
    std::vector<SDL_Event> get_input_events() { return m_Renderer.get_input_events(); }

    virtual void update(float dT) override;
};

