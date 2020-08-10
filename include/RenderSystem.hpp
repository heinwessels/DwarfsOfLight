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

    double m_scaling = 32; // TEMPORARY BEFORE IMPLEMENTING CAMERA

public:
    RenderSystem(Game &game, int width, int height);
    std::vector<SDL_Event> get_input_events() { return m_Renderer.get_input_events(); }

    virtual void internal_update(double dT) override;

private:
    void load_texture_if_not_loaded(Renderable &renderable);

    void update_entities();
    void update_world();
};

