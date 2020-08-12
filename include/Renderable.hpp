#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "Component.hpp"
#include "Types.hpp"
#include "MTexture.hpp"
#include "MColour.hpp"

class Renderable : public Component{
    MTexture m_texture;
public:
    double width = 0, height = 0;
    Renderable (std::string path, double width, double height, int atlas_rows, int atlas_columns, int atlas_index_x, int atlas_index_y)
            : Component(RenderComponentID),
            m_texture(path, atlas_rows, atlas_columns, atlas_index_x, atlas_index_y),
            width(width), height(height) { };
    Renderable (std::string path, double width, double height)
            : Renderable(path, width, height, 1, 1, 0, 0)
            { };
    bool is_texture_loaded() {return m_texture.is_texture_loaded();}
    bool is_visible() {return m_texture.is_visible(); }
    MTexture &get_mtexture () { return m_texture; }
    std::string get_texture_path () { return m_texture.get_path(); }
};