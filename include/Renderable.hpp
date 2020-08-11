#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "Component.hpp"
#include "Types.hpp"
#include "MTexture.hpp"
#include "MColour.hpp"

class Renderable : public Component{
    std::string m_path;
    MTexture m_texture;
public:
    double width = 0, height = 0;
    Renderable (std::string path, double width, double height)
            : Component(RenderComponentID), m_path(path), width(width), height(height) { };
    bool is_texture_loaded() {return m_texture.is_texture_loaded();}
    bool is_visible() {return m_texture.is_visible(); }
    MTexture &get_mtexture () { return m_texture; }
    std::string get_texture_path () { return m_path; }
};