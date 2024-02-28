//
// Created by Vlad Puscaru on 28.02.2024.
//

#include "Game.h"

Game::Game(int wWidth, int wHeight, const std::string &wTitle)
    : m_window(sf::VideoMode(wWidth, wHeight), wTitle)
{

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


    m_window.display();
}
