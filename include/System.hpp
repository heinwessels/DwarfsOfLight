#pragma once

class Game;
class System{

    Game &game;


public:
    System (Game &game) : game(game) { }
    virtual void update(Game &game, float dT) = 0;
};
