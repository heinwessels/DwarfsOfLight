#include "RenderSystem.hpp"
#include "Game.hpp"

RenderSystem::RenderSystem(Game &game, int width, int height)
    : System(game, std::string("Render System")), m_Renderer(width, height)
{
    m_signature |= Component::get_component_signature(RenderComponentID);

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

        // Now draw it
        m_Renderer.renderTextureToScreen(
            renderable.get_mtexture().get_texture(),
            x*m_scaling, y*m_scaling,
            renderable.width*m_scaling, renderable.height*m_scaling
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
    if (!renderable.is_texture_loaded()){
        int width = 0, height = 0;
        SDL_Texture* texture = m_Renderer.load_texture(renderable.get_texture_path(), width, height);
        renderable.get_mtexture().set_texture(texture, width, height);
    }
}
