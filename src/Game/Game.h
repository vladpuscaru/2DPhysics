//
// Created by Vlad Puscaru on 28.02.2024.
//

#ifndef PHYSICS_ENGINE_GAME_H
#define PHYSICS_ENGINE_GAME_H

#include <SFML/Graphics.hpp>
#include "../OVTVector/OVTVector.h"
#include "../OVTRigidBody/OVTRigidBody.h"
#include "../OVTMath/OVTMath.h"
#include "../OVTCollisions/OVTCollisions.h"


class Game {
private:
    sf::RenderWindow m_window;

    std::vector<OVTRigidBody> m_bodies;
    std::vector<sf::CircleShape> m_circles;
    std::vector<sf::RectangleShape> m_rects;

    bool m_isMovingLeft = false;
    bool m_isMovingRight = false;
    bool m_isMovingUp = false;
    bool m_isMovingDown = false;

    void init();

    void input();
    void update(float deltaTime);
    void render();

    void generateRandomBodies();
    sf::Color getRandomColor() const;
public:
    Game(int wWidth, int wHeight, const std::string &wTitle);

    void run();
};


#endif //PHYSICS_ENGINE_GAME_H
