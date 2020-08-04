#include "Renderer.hpp"

Renderer::Renderer(int width, int height)
     : width(width), height(height)
{
    init_window();
}

void Renderer::clear_screen(){
    SDL_SetRenderDrawColor( m_pSdlRenderer, 0, 0, 0, 0 );
    SDL_RenderClear(m_pSdlRenderer);
}
void Renderer::show_screen(){
    SDL_RenderPresent( m_pSdlRenderer );
}
std::vector<SDL_Event> Renderer::get_input_events(){
    std::vector<SDL_Event> events;
    SDL_GetKeyboardState(NULL);
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        events.push_back(event);
    }
    return events;
}

void Renderer::renderTextureToScreen(SDL_Texture *texture, float x, float y, float width, float height){
    SDL_Rect screen_location;
    screen_location.x = x - width / 2.0;
    screen_location.y = y - height / 2.0;
    screen_location.w = width;
    screen_location.h = height;
    SDL_RenderCopy( m_pSdlRenderer, texture, NULL, &screen_location );
}

SDL_Texture* Renderer::load_texture(std::string path)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( m_pSdlRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

bool Renderer::init_window(){
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        m_pSdlWindow = SDL_CreateWindow(
            "Dwarfs of Light", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height, SDL_WINDOW_SHOWN
        );
        if (m_pSdlWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Create renderer for window
            m_pSdlRenderer = SDL_CreateRenderer(m_pSdlWindow, -1, SDL_RENDERER_ACCELERATED);
            if (m_pSdlRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Setup the font
                TTF_Init();
                m_pFont = TTF_OpenFont(m_fontPath, 30);
                if (m_pFont == NULL) {
                    fprintf(stderr, "error: font not found\n");
                    exit(EXIT_FAILURE);
                }
            }

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
        }
    }

    return success;
}