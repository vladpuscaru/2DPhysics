//
// Created by Vlad Puscaru on 28.02.2024.
//

#ifndef PHYSICS_ENGINE_GAME_H
#define PHYSICS_ENGINE_GAME_H

#include <SFML/Graphics.hpp>
#include "../OVTVector/OVTVector.h"

class Game {
private:
    sf::RenderWindow m_window;

    void input();
    void update();
    void render();

public:
    Game(int wWidth, int wHeight, const std::string &wTitle);

    void run();
};


#endif //PHYSICS_ENGINE_GAME_H
