#include "RenderSystem.hpp"
#include "Game.hpp"

RenderSystem::RenderSystem(Game &game, int width, int height)
    : System(game, std::string("Render System")),
    m_Renderer(width, height),
    m_camera(Vec2(0, 0), 32, Vec2(width, height)),
    m_texturepool(m_Renderer)
{
    m_signature |= Component::get_component_signature(RenderComponentID);
}

void RenderSystem::init(){
    // Load all textures of current world and entities on startup.
    load_all_textures();
}

void RenderSystem::update(double dT){

    m_Renderer.clear_screen();

    update_world(); // World drawn first cause it's in the background
    update_entities();

    m_Renderer.show_screen();
}

void RenderSystem::update_entities(){
    for(auto const &entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){

            Vec2 pos = entity->get_posision();
            Renderable &renderable = static_cast<Renderable&>(entity->get_component(RenderComponentID));

            draw_renderable(pos.x, pos.y, renderable);
        }
    }
}

void RenderSystem::update_world(){

    for(auto &column : m_pgame.get_world().get_tiles()){
        for (auto &tile : column){
            if (tile.has_component(RenderComponentID)){

                Vec2 pos = tile.get_posision();
                Renderable &renderable = static_cast<Renderable&>(tile.get_component(RenderComponentID));

                draw_renderable(pos.x, pos.y, renderable);
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

        double zoom = m_camera.get_zoom();
        Vec2 position_to_draw = m_camera.get_position_on_screen(Vec2(x, y));

        // Get the texture
        MTexture & texture = m_texturepool.get_texture_from_pool(renderable.get_texture_path());

        // Calculate the source rectangle
        SDL_Rect source_rect = renderable.get_source_rect();
        source_rect.w = texture.get_width() / source_rect.w;
        source_rect.h = texture.get_height() / source_rect.h;
        source_rect.x = source_rect.x * source_rect.w;
        source_rect.y = source_rect.y * source_rect.h;

        // Get the colour modulation for this texture
        texture.set_colour_mod(renderable.get_colour_mod());

        // Finally draw it
        m_Renderer.renderTextureToScreen(
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
            Renderable &renderable = static_cast<Renderable&>(entity->get_component(RenderComponentID));
            load_texture_if_not_loaded(renderable);
        }
    }
    for(auto &column : m_pgame.get_world().get_tiles()){
        for (auto &tile : column){
            if (tile.has_component(RenderComponentID)){
                Renderable &renderable = static_cast<Renderable&>(tile.get_component(RenderComponentID));
                load_texture_if_not_loaded(renderable);
            }
        }
    }
}

void RenderSystem::load_texture_if_not_loaded(Renderable &renderable){
    if (!m_texturepool.is_texture_in_pool(renderable.get_texture_path())){
        m_texturepool.load_texture_into_pool(renderable.get_texture_path());
    }
}
