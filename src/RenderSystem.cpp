#include "RenderSystem.hpp"
#include "Game.hpp"
#include "World.hpp"

#include "TransformComponent.hpp"
#include "Renderable.hpp"

RenderSystem::RenderSystem(Game &game, int width, int height)
    : System(game, std::string("Render System")),
    m_pRenderer(std::make_unique<Renderer>(width, height)),
    m_pCamera(std::make_unique<Camera>(Vec2(width/2.0, height/2.0), 32, Vec2(width, height))),
    m_pTexturepool(std::make_unique<TexturePool>(*m_pRenderer))
{
    m_signature |= Component::get_component_signature<TransformComponent>();
    m_signature |= Component::get_component_signature<Renderable>();
}

void RenderSystem::init(){
    // Load all textures of current world and entities on startup.
    load_all_textures();
}

void RenderSystem::update(double dT){

    m_pRenderer->clear_screen();

    update_world(); // World drawn first cause it's in the background
    update_entities();

    m_pRenderer->show_screen();
}

std::vector<SDL_Event> RenderSystem::get_input_events() { return m_pRenderer->get_input_events(); }
void RenderSystem::set_camera_zoom(double zoom) { m_pCamera->set_zoom(zoom); }
void RenderSystem::set_camera_target(Vec2 *target) { m_pCamera->set_target(target); }

void RenderSystem::update_entities(){
    for(auto const &entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){

            TransformComponent &transform = entity->get_component<TransformComponent>();
            Renderable &renderable = entity->get_component<Renderable>();

            draw_renderable(transform.position.x, transform.position.y, renderable);
        }
    }
}

void RenderSystem::update_world(){

    for(auto &column : m_pgame.get_world().get_tiles()){
        for (auto &tile : column){
            if (tile.has_component<Renderable>()){

                TransformComponent &transform = tile.get_component<TransformComponent>();
                Renderable &renderable = tile.get_component<Renderable>();

                draw_renderable(transform.position.x, transform.position.y, renderable);
            }
        }
    }
}

void RenderSystem::draw_renderable(double x, double y, Renderable &renderable){

    // Always keep all textures loaded
    load_texture_if_not_loaded(renderable);

    // Renderable could be hidden or the colour modulation makes it invisible.
    // Don't try to draw it then
    if (renderable.is_visible()){

        double zoom = m_pCamera->get_zoom();
        Vec2 position_to_draw = m_pCamera->get_position_on_screen(Vec2(x, y));

        // Get the texture
        MTexture & texture = m_pTexturepool->get_texture_from_pool(renderable.get_texture_path());

        // Calculate the source rectangle
        SDL_Rect source_rect = renderable.get_source_rect();
        source_rect.w = texture.get_width() / source_rect.w;
        source_rect.h = texture.get_height() / source_rect.h;
        source_rect.x = source_rect.x * source_rect.w;
        source_rect.y = source_rect.y * source_rect.h;

        // Get the colour modulation for this texture
        texture.set_colour_mod(renderable.get_colour_mod());

        // Finally draw it
        m_pRenderer->renderTextureToScreen(
            texture.get_texture(),
            source_rect,
            position_to_draw.x, position_to_draw.y,
            renderable.width*zoom, renderable.height*zoom
        );
    }
}


void RenderSystem::load_all_textures(){
    for(auto const &entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){
            Renderable &renderable = entity->get_component<Renderable>();
            load_texture_if_not_loaded(renderable);
        }
    }
    for(auto &column : m_pgame.get_world().get_tiles()){
        for (auto &tile : column){
            if (tile.has_component<Renderable>()){
                Renderable &renderable = tile.get_component<Renderable>();
                load_texture_if_not_loaded(renderable);
            }
        }
    }
}

void RenderSystem::load_texture_if_not_loaded(Renderable &renderable){
    if (!m_pTexturepool->is_texture_in_pool(renderable.get_texture_path())){
        m_pTexturepool->load_texture_into_pool(renderable.get_texture_path());
    }
}
