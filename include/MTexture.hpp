#pragma once

#include <string>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "MColour.hpp"

//Texture wrapper class
class MTexture
{
    public:
        MTexture(std::string path, int atlas_rows, int atlas_columns, int index_x, int index_y)
            : m_path(path),
            m_atlas_rows(atlas_rows), m_atlas_columns(atlas_columns),
            m_atlas_index_x (index_x), m_atlas_index_y(index_y)
            { }
        MTexture(std::string path)
            :  MTexture(path, 1, 1, 0, 0)
            { };

        ~MTexture(){ free(); };

        void free(){
            if( m_texture != NULL )
            {
                SDL_DestroyTexture( m_texture );
                m_texture = NULL;
                m_texture_width = 0;
                m_texture_height = 0;
            }
        }
        bool is_texture_loaded() {return m_texture != NULL;}
        void set_colour_mod( MColour colour ){
            SDL_SetTextureColorMod( m_texture, colour.r, colour.g, colour.b );
            m_colour_mod = colour;
        };    // This modulates the colour by eg <r/255>
        MColour get_colour_mod(){ return m_colour_mod; }

        std::string get_path() { return m_path; }
        void set_texture(SDL_Texture* texture, int width, int height){
            free();
            m_texture = texture;
            m_texture_width = width;
            m_texture_height = height;

            set_source_rect();
        }
        SDL_Texture *get_texture() { return m_texture; }

        void hide() { m_hide = true; }
        void show() { m_hide = false; }
        bool hidden() { return m_hide; }

        // This texture is visible if it's not hidden and at least one channel is not zero
        bool is_visible() { return !hidden() && (m_colour_mod.r || m_colour_mod.g || m_colour_mod.b); }

        int get_width() { return m_texture_width; };
        int get_height() {return m_texture_height; };

        void set_source_rect_index(int x, int y) {
            // <x, y> indexes start at 0.
            m_source_rect.x = x * m_source_rect.w;
            m_source_rect.y = y * m_source_rect.h;
        }
        SDL_Rect get_source_rect() { return m_source_rect; }

    private:

        SDL_Texture* m_texture = NULL;
        std::string m_path;

        int m_texture_width = 0;
        int m_texture_height = 0;

        bool m_hide = false;

        MColour m_colour_mod = {255};    // Default fully visible

        int m_atlas_rows, m_atlas_columns;
        int m_atlas_index_x, m_atlas_index_y;
        SDL_Rect m_source_rect;

        void set_source_rect(){
            m_source_rect.w = m_texture_width / m_atlas_columns;
            m_source_rect.h = m_texture_height / m_atlas_rows;
            set_source_rect_index(m_atlas_index_x, m_atlas_index_y);
        }

};