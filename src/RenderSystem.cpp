#include "RenderSystem.hpp"
#include "Game.hpp"

void MTexture::set_texture(SDL_Texture* texture, int width, int height){
    free();
    m_texture = texture;
    m_width = width;
    m_height = height;
}

void MTexture::free(){
    if( m_texture != NULL )
    {
        SDL_DestroyTexture( m_texture );
        m_texture = NULL;
        m_width = 0;
        m_height = 0;
    }
}

RenderSystem::RenderSystem(Game &game, int width, int height)
    : System(game), m_Renderer(width, height)
{
    m_signature |= Component::get_component_signature(RenderComponentID);
}

void RenderSystem::update(float dT){

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

            // This is a hacky solution to only load textures the first time they're drawn. Rather load on startup.
            // TODO Load all textures function.
            load_texture_if_not_loaded(renderable);

            m_Renderer.renderTextureToScreen(
                renderable.get_mtexture().get_texture(),
                pos.x, pos.y,
                renderable.width, renderable.height
            );

        }
    }
}

void RenderSystem::update_world(){

    for(auto &tile : m_pgame.get_world().get_tiles()){
        if (tile.has_component(RenderComponentID)){

            Vec2 pos = tile.get_posision();
            Renderable &renderable = static_cast<Renderable&>(tile.get_component(RenderComponentID));

            // This is a hacky solution to only load textures the first time they're drawn. Rather load on startup.
            // TODO Load all textures function.
            load_texture_if_not_loaded(renderable);

            m_Renderer.renderTextureToScreen(
                renderable.get_mtexture().get_texture(),
                pos.x, pos.y,
                renderable.width, renderable.height
            );
        }
    }
}

// void RenderSystem::draw_renderable(){

// }

void RenderSystem::load_texture_if_not_loaded(Renderable &renderable){
    if (!renderable.is_texture_loaded()){
        int width = 0, height = 0;
        SDL_Texture* texture = m_Renderer.load_texture(renderable.get_texture_path(), width, height);
        renderable.get_mtexture().set_texture(texture, width, height);
    }
}