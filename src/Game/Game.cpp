//
// Created by Vlad Puscaru on 28.02.2024.
//

#include "Game.h"

Game::Game(int wWidth, int wHeight, const std::string &wTitle)
        : m_window(sf::VideoMode(wWidth, wHeight), wTitle) {
    init();
}

void Game::run() {
    sf::Clock deltaClock;

    while (m_window.isOpen()) {
        float deltaTime = deltaClock.restart().asSeconds();
        input();
        update(deltaTime);
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
                    break;
                case sf::Keyboard::G:
                    generateRandomBodies();
                    break;
                case sf::Keyboard::W:
                    m_isMovingUp = true;
                    break;
                case sf::Keyboard::A:
                    m_isMovingLeft = true;
                    break;
                case sf::Keyboard::S:
                    m_isMovingDown = true;
                    break;
                case sf::Keyboard::D:
                    m_isMovingRight = true;
                    break;
            }
        } else if (event.type == sf::Event::KeyReleased) {
            switch (event.key.code) {
                case sf::Keyboard::W:
                    m_isMovingUp = false;
                    break;
                case sf::Keyboard::A:
                    m_isMovingLeft = false;
                    break;
                case sf::Keyboard::S:
                    m_isMovingDown = false;
                    break;
                case sf::Keyboard::D:
                    m_isMovingRight = false;
                    break;
            }
        }
    }
}

void Game::update(float deltaTime) {

    // Move Player
    float dx = 0;
    float dy = 0;
    float speed = 367.f;

    if (m_isMovingRight) dx++;
    if (m_isMovingLeft) dx--;
    if (m_isMovingUp) dy--;
    if (m_isMovingDown) dy++;

    if (dx != 0 || dy != 0) {
        OVTVector direction = OVTMath::normalize({dx, dy});
        OVTVector velocity = direction * speed * deltaTime;
        m_bodies[0].move(velocity);
    }

    // Check Collisions
    for (int i = 0; i < m_bodies.size() - 1; i++) {
        for (int j = i + 1; j < m_bodies.size(); j++) {
            if (i == j) continue;

            auto &bodyA = m_bodies[i];
            auto &bodyB = m_bodies[j];

            CollisionManifold collision;
            collision.isCollision = false;

            if (bodyA.m_shape == ShapeType::Circle && bodyB.m_shape == ShapeType::Circle) {
                collision = OVTCollisions::intersectCircle(bodyA.m_position, bodyA.m_radius, bodyB.m_position, bodyB.m_radius);
            } else {
                collision = OVTCollisions::intersectPolygons(bodyA.getTransformedVertices(), bodyB.getTransformedVertices());
            }

            if (collision.isCollision) {
                bodyA.move(-collision.normal * collision.depth / 2.f);
                bodyB.move(collision.normal * collision.depth / 2.f);
            }
        }
    }

    for (auto& body : m_bodies) {
        body.rotate(M_PI / 2 * deltaTime);
    }
}

void Game::render() {
    m_window.clear({84, 83, 82});

    sf::RectangleShape rect;
    sf::CircleShape circle;

    for (int i = 0; i < m_bodies.size(); i++) {
        auto& body = m_bodies[i];
        if (body.m_shape == ShapeType::Circle) {
            circle.setRadius(body.m_radius);
            circle.setPosition({body.m_position.x - body.m_radius, body.m_position.y - body.m_radius});
            circle.setRotation(body.m_rotationAngle * 180 / M_PI); // body has it in radians, SFML needs it in angles
            circle.setFillColor(m_colors[i]);
            circle.setOutlineColor(sf::Color::White);

            m_window.draw(circle);
        } else if (body.m_shape == ShapeType::Square) {
            rect.setSize({body.m_width, body.m_height});
            rect.setOrigin({body.m_width / 2, body.m_height / 2});
            rect.setPosition({body.m_position.x, body.m_position.y});
            rect.setRotation(body.m_rotationAngle * 180 / M_PI); // body has it in radians, SFML needs it in angles
            rect.setFillColor(m_colors[i]);
            rect.setOutlineColor(sf::Color::White);

            m_window.draw(rect);
        }
    }

    m_window.display();
}

void Game::init() {
    generateRandomBodies();
}

void Game::generateRandomBodies() {
    m_bodies.clear();
    for (int i = 0; i < 20; i++) {
        if (i == 0) {
            float width = 55.5f;
            float height = 50.5f;
            float x = 0;
            float y = 0;
            auto body = OVTRigidBody::createSquareBody(width, height, {x, y}, 5, .4f, false);
            m_bodies.emplace_back(body);
        }

        bool isCircle = !(std::rand() % 1 == 0);
        if (isCircle) {
            float radius = 15.5f;
            float x = std::clamp<float>(std::rand() % m_window.getSize().x, radius, m_window.getSize().x - radius * 2);
            float y = std::clamp<float>(std::rand() % m_window.getSize().y, radius, m_window.getSize().y - radius * 2);
            auto body = OVTRigidBody::createCircleBody(radius, {x, y}, 3, 1, false);
            m_bodies.emplace_back(body);
        } else {
            float width = 55.5f;
            float height = 50.5f;
            float x = std::clamp<float>(std::rand() % m_window.getSize().x, width / 2, m_window.getSize().x - width);
            float y = std::clamp<float>(std::rand() % m_window.getSize().y, height / 2, m_window.getSize().y - height);
            auto body = OVTRigidBody::createSquareBody(width, height, {x, y}, 5, .4f, false);
            m_bodies.emplace_back(body);
        }
        m_colors.emplace_back(getRandomColor());
    }
}

sf::Color Game::getRandomColor() const {
    static std::vector<sf::Color> colors = {
            sf::Color::Black,
            sf::Color::Yellow,
            sf::Color::White,
            sf::Color::Blue,
            sf::Color::Cyan,
            sf::Color::Red,
            sf::Color::Green,
            sf::Color::Magenta,
    };

    int randIdx = std::rand() % colors.size();
    return colors[randIdx];
}