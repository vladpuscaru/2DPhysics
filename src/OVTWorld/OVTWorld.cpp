//
// Created by Vlad Puscaru on 28.02.2024.
//

#include "OVTWorld.h"

OVTWorld::OVTWorld()
        : m_gravity(0.0f, 9.8f) {

}

OVTRigidBody &OVTWorld::getBody(int idx) {
    assert(idx >= 0 && idx < m_bodies.size());
    return *m_bodies[idx];
}

void OVTWorld::step(float deltaTime) {

    // Movement Step
    for (auto &body: m_bodies) {
        body->step(deltaTime);
    }

    // Collision Step
    for (int i = 0; i < m_bodies.size() - 1; i++) {
        for (int j = i + 1; j < m_bodies.size(); j++) {
            if (i == j) continue;

            auto &bodyA = m_bodies[i];
            auto &bodyB = m_bodies[j];

            CollisionManifold collision = isCollision(*bodyA, *bodyB);
            if (collision.isCollision) {
                bodyA->move(-collision.normal * collision.depth / 2.f);
                bodyB->move(collision.normal * collision.depth / 2.f);
            }
        }
    }

    for (auto &body: m_bodies) {
        body->rotate(M_PI / 2 * deltaTime);
    }
}

void OVTWorld::addBody(const OVTRigidBody &body) {
    m_bodies.emplace_back(std::make_shared<OVTRigidBody>(body));
}

void OVTWorld::removeBody(const OVTRigidBody &body) {
    for (auto it = m_bodies.begin(); it != m_bodies.end(); it++) {
        if ((*(*it)).m_id == body.m_id) {
            m_bodies.erase(it);
            break;
        }
    }
}

CollisionManifold OVTWorld::isCollision(OVTRigidBody &bodyA, OVTRigidBody &bodyB) {
    if (bodyA.m_shape == ShapeType::Square) {
        if (bodyB.m_shape == ShapeType::Square) {
            return OVTCollisions::intersectPolygons(bodyA.getTransformedVertices(), bodyB.getTransformedVertices());
        } else if (bodyB.m_shape == ShapeType::Circle) {
            CollisionManifold manifold = OVTCollisions::intersectCirclePolygon(bodyB.m_position, bodyB.m_radius,
                                                         bodyA.getTransformedVertices());
            manifold.normal = -manifold.normal;
            return manifold;
        }
    } else if (bodyA.m_shape == ShapeType::Circle) {
        if (bodyB.m_shape == ShapeType::Square) {
            return OVTCollisions::intersectCirclePolygon(bodyA.m_position, bodyA.m_radius,
                                                         bodyB.getTransformedVertices());
        } else if (bodyB.m_shape == ShapeType::Circle) {
            return OVTCollisions::intersectCircle(bodyA.m_position, bodyA.m_radius, bodyB.m_position, bodyB.m_radius);
        }
    }
}

int OVTWorld::getBodyCount() const {
    return m_bodies.size();
}

void OVTWorld::clear() {
    m_bodies.clear();
}
