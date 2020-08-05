#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "Component.hpp"
#include "Types.hpp"
#include "MColour.hpp"

//Texture wrapper class
class MTexture
{
    public:
        MTexture() { };
        ~MTexture(){ free(); };

        void free();
        bool is_texture_loaded() {return m_texture != NULL;}
        void setColor( Uint8 red, Uint8 green, Uint8 blue ){SDL_SetTextureColorMod( m_texture, red, green, blue );};

        void set_texture(SDL_Texture* texture, int width, int height);
        SDL_Texture *get_texture() { return m_texture; }

        //Gets image dimensions
        int get_width() { return m_width; };
        int get_height() {return m_height; };

    private:
        //The actual hardware texture
        SDL_Texture* m_texture = NULL;

        //Image dimensions
        int m_width = 0;
        int m_height = 0;
};


class Renderable : public Component{
    std::string m_path;
    MTexture m_texture;
public:
    float width = 0, height = 0;
    Renderable (std::string path, float width, float height)
            : Component(RenderComponentID), m_path(path), width(width), height(height) { };
    bool is_texture_loaded() {return m_texture.is_texture_loaded();}
    MTexture &get_mtexture () { return m_texture; }
    std::string get_texture_path () { return m_path; }
};