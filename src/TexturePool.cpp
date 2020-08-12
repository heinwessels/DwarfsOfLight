#include "TexturePool.hpp"

TexturePool::TexturePool(Renderer &renderer)
    : m_pRenderer(renderer)
{

}

MTexture& TexturePool::get_texture_from_pool(std::string path){
    return m_texturepool.at(path);
}

bool TexturePool::is_texture_in_pool(std::string path){
    return m_texturepool.find(path) != m_texturepool.end();
}

void TexturePool::load_texture_into_pool(std::string path){

    // Can't create a temporary MTexture here,
    // otherwise it will free the texture in the pool
    // as well when it goes out of scope.
    m_texturepool.emplace(path, MTexture(path));
    MTexture &texture = get_texture_from_pool(path);

    int width = 0, height = 0;
    SDL_Texture *raw_texture = m_pRenderer.load_texture(path, width, height);
    texture.set_texture(raw_texture, width, height);
}