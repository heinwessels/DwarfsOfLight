#include "Application.hpp"

Application::Application()
    : m_game(Game())
{
}

void Application::run(){

    bool quit = false;
    while(!quit){

        m_game.step(0.0);

    }
}