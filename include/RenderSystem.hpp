#pragma once

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "GameObject.hpp"

class RenderSystem{
    /*
    This handles all things rendering. It's heavily based on this guide:
    https://lazyfoo.net/tutorials/SDL/
    */


    const char * m_fontPath = "fonts/Thintel.ttf";

    SDL_Renderer* m_pSdlRenderer;
    SDL_Window* m_pSdlWindow;
    TTF_Font* m_pFont;

public:

    int width, height;

    RenderSystem(int width, int height);

    void clear_screen();
    void show_screen();

    void renderTextureToScreen(SDL_Texture *texture);
    SDL_Texture* loadTexture( std::string path );

private:

    bool init_window();
};