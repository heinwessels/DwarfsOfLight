#pragma once

#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Renderer{
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

    Renderer(int width, int height);

    void clear_screen();
    void show_screen();
    std::vector<SDL_Event> get_input_events();

    void renderTextureToScreen(SDL_Texture *texture, float x, float y, float width, float height);
    SDL_Texture* load_texture( std::string path );

private:

    bool init_window();
};