#pragma once

#include <string>
#include <unordered_map>

#include "MTexture.hpp"
#include "Renderer.hpp"

class TexturePool{

    std::unordered_map<std::string, MTexture> m_texturepool;
    Renderer &m_pRenderer;

public:

    TexturePool(Renderer &renderer);

    bool is_texture_in_pool(std::string path);
    MTexture& get_texture_from_pool(std::string path);
    void load_texture_into_pool(std::string path);
};