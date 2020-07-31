#pragma once

class Game;
class System{


protected:
    Game& m_pGame;

public:
    System(Game &game) : m_pGame(game) { }
    virtual void update(float dT) = 0;
};