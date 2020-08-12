#pragma once

#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Renderer.hpp"
#include "Camera.hpp"
#include "TexturePool.hpp"

#include "System.hpp"
#include "Entity.hpp"
#include "Renderable.hpp"

class Game;
class RenderSystem : public System{

    Renderer m_Renderer;
    Camera m_camera;
    TexturePool m_texturepool;

public:
    RenderSystem(Game &game, int width, int height);
    std::vector<SDL_Event> get_input_events() { return m_Renderer.get_input_events(); }

    virtual void init() override;
    virtual void update(double dT) override;

    void set_camera_zoom(double zoom) { m_camera.set_zoom(zoom); }
    void set_camera_target(Vec2 *target) { m_camera.set_target(target); }

private:
    void draw_renderable(double x, double y, Renderable &renderable);
    void load_texture_if_not_loaded(Renderable &renderable);
    void load_all_textures();

    void update_entities();
    void update_world();
};

