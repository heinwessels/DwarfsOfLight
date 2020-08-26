#pragma once

#include "System.hpp"

#include <memory>
#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Renderer.hpp"
#include "Camera.hpp"
#include "TexturePool.hpp"

class Renderable;
class Game;
class RenderSystem : public System{

    std::unique_ptr<Renderer> m_pRenderer;
    std::unique_ptr<Camera> m_pCamera;
    std::unique_ptr<TexturePool> m_pTexturepool;

public:
    RenderSystem(Game &game, int width, int height);
    std::vector<SDL_Event> get_input_events();

    virtual void init() override;
    virtual void update(double dT) override;

    void set_camera_zoom(double zoom);
    void set_camera_target(Vec2 *target);
    void set_camera_position(Vec2 position) { m_pCamera->set_position(position); }

private:
    void sort_entities_for_rendering();
    static bool entity_sort_first(const std::unique_ptr<Entity> &a, const std::unique_ptr<Entity> &b);

    void draw_renderable(double x, double y, Renderable &renderable);
    void load_texture_if_not_loaded(Renderable &renderable);
    void load_all_textures();

    void update_entities();
    void update_world();
};

