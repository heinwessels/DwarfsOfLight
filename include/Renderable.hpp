#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "Component.hpp"
#include "Types.hpp"
#include "MTexture.hpp"
#include "MColour.hpp"

class Renderable : public Component{
    std::string m_texture_path;     // Basically a pointer to the texture in the texturepool
    int m_texture_rows, m_texture_columns;
    int m_texture_index_x, m_texture_index_y;
    MColour m_colour_mod = {255};
    bool m_hide = false;

public:
    static constexpr ComponentID ID = RenderComponentID;

    double width = 0, height = 0;
    Renderable (std::string texture_path, double width, double height, int texture_rows, int texture_columns, int texture_index_x, int texture_index_y)
            : Component(ID),
            m_texture_path(texture_path),
            m_texture_rows(texture_rows), m_texture_columns(texture_columns),
            m_texture_index_x(texture_index_x), m_texture_index_y(texture_index_y),
            width(width), height(height)
            { };
    Renderable (std::string texture_path, double width, double height)
            : Renderable(texture_path, width, height, 1, 1, 0, 0)
            { };

    std::string get_texture_path() { return m_texture_path; }
    SDL_Rect get_source_rect(){
        // This is a scaling number, and requires the spite witdth
        SDL_Rect rect;
        rect.x = m_texture_index_x;
        rect.y = m_texture_index_y;
        rect.w = m_texture_columns;
        rect.h = m_texture_rows;
        return rect;
    }

    void set_colour_mod(MColour colour) { m_colour_mod = colour;}
    MColour get_colour_mod() {return m_colour_mod; }

    void hide() { m_hide = true; }
    void show() { m_hide = false; }
    bool hidden() { return m_hide; }

     // This renderable is visible if it's not hidden and at least one channel is not zero
    bool is_visible() { return !hidden() && (m_colour_mod.r || m_colour_mod.g || m_colour_mod.b); }
};