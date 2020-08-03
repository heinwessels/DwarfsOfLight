#include "Application.hpp"

Application::Application()
    : m_game(Game())
{
}

void Application::run(){

    float fps = 30.0;

    bool nquit = true;
    while(nquit){

        nquit = m_game.step(1.0/fps);

        usleep(1.0/fps * 1000.0);
    }
}