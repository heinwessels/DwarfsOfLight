#pragma once

#include <string>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "MColour.hpp"

//Texture wrapper class
class MTexture
{
    public:
        MTexture(std::string path)
            :  m_path(path)
            { }

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
        };    // This modulates the colour by eg <r/255>

        std::string get_path() { return m_path; }
        void set_texture(SDL_Texture* texture, int width, int height){
            free();
            m_texture = texture;
            m_texture_width = width;
            m_texture_height = height;
        }
        SDL_Texture *get_texture() { return m_texture; }

        int get_width() { return m_texture_width; };
        int get_height() {return m_texture_height; };

    private:

        SDL_Texture* m_texture = NULL;
        std::string m_path;

        int m_texture_width = 0;
        int m_texture_height = 0;

};