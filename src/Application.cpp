#include "Application.hpp"

Application::Application()
    : m_game(Game())
{
}

void Application::run(){

    bool nquit = true;
    while(nquit){

        nquit = m_game.step(0.0);

    }
}