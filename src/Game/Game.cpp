//
// Created by Vlad Puscaru on 28.02.2024.
//

#include "Game.h"

Game::Game(int wWidth, int wHeight, const std::string &wTitle)
        : m_window(sf::VideoMode(wWidth, wHeight), wTitle) {
    init();
}

void Game::run() {
    while (m_window.isOpen()) {
        input();
        update();
        render();
    }
}

void Game::input() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Q:
                    m_window.close();
            }
        }
    }
}

void Game::update() {

}

void Game::render() {
    m_window.clear(sf::Color::Blue);

    sf::CircleShape circle;
    sf::RectangleShape rect;

    for (auto body : m_bodies) {
        switch (body.m_shape) {
            case ShapeType::Circle:
                circle.setRadius(body.m_radius);
                circle.setPosition({ body.m_position.x, body.m_position.y });
                circle.setFillColor(sf::Color::Black);
                circle.setOutlineColor(sf::Color::Red);
                circle.setOutlineThickness(1.8f);

                m_window.draw(circle);
                break;
            case ShapeType::Square:
                rect.setSize({ body.m_width, body.m_height });
                rect.setPosition({ body.m_position.x, body.m_position.y });
                rect.setFillColor(sf::Color::White);
                rect.setOutlineColor(sf::Color::Black);
                rect.setOutlineThickness(1.8f);

                m_window.draw(rect);
                break;
        }
    }

    m_window.display();
}

void Game::init() {
    for (int i = 0; i < 10; i++) {
        auto body = i % 2 ?
                    OVTRigidBody::createCircleBody(15, {10.f + (i * 15), 10.f + (i * 15)}, 3, 1, false)
                          :
                    OVTRigidBody::createSquareBody(100, 40, {30.f + (i * 100), 50.f + (i * 40)}, 5, .4f, false);

        m_bodies.emplace_back(body);
    }
}
