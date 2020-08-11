#include "Application.hpp"

Application::Application()
    : m_game(Game())
{
}

void Application::run(){

    using clock = std::chrono::system_clock;
    using sec = std::chrono::duration<double>;

    double fps = 20.0;

    bool nquit = true;
    while(nquit){

        auto loop_start = clock::now();

        nquit = m_game.update(1.0/fps);

        const auto loop_end = clock::now();

        sec loop_time = loop_end - loop_start;
        if(loop_time.count() < 1.0/fps){
            // If there is still time left before the next frame must be drawn
            SDL_Delay((1.0/fps - loop_time.count()) * 1000.0);
        }
    }
}