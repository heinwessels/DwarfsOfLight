#pragma once

#include <SDL2/SDL.h>

#include "MColour.hpp"

//Texture wrapper class
class MTexture
{
    public:
        MTexture() { };
        ~MTexture(){ free(); };

        void free(){
            if( m_texture != NULL )
            {
                SDL_DestroyTexture( m_texture );
                m_texture = NULL;
                m_width = 0;
                m_height = 0;
            }
        }
        bool is_texture_loaded() {return m_texture != NULL;}
        void set_colour_mod( MColour colour ){
            SDL_SetTextureColorMod( m_texture, colour.r, colour.g, colour.b );
            m_colour_mod = colour;
        };    // This modulates the colour by eg <r/255>
        MColour get_colour_mod(){ return m_colour_mod; }

        void set_texture(SDL_Texture* texture, int width, int height){
            free();
            m_texture = texture;
            m_width = width;
            m_height = height;

            m_source_rect.x = 0;
            m_source_rect.y = 0;
            m_source_rect.w = width;
            m_source_rect.h = height;
        }
        SDL_Texture *get_texture() { return m_texture; }

        void hide() { m_hide = true; }
        void show() { m_hide = false; }
        bool hidden() { return m_hide; }

        // This texture is visible if it's not hidden and at least one
        bool is_visible() { return !hidden() && (m_colour_mod.r || m_colour_mod.g || m_colour_mod.b); }

        int get_width() { return m_width; };
        int get_height() {return m_height; };

        SDL_Rect get_source_rect() { return m_source_rect; }

    private:

        SDL_Texture* m_texture = NULL;

        int m_width = 0;
        int m_height = 0;

        bool m_hide = false;

        MColour m_colour_mod = {255};    // Default fully visible

        SDL_Rect m_source_rect;

};