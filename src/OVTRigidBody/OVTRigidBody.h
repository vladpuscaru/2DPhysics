//
// Created by Vlad Puscaru on 28.02.2024.
//

#ifndef PHYSICS_ENGINE_OVTRIGIDBODY_H
#define PHYSICS_ENGINE_OVTRIGIDBODY_H

#include "../OVTVector/OVTVector.h"

#include <iostream>
#include <cmath>

enum ShapeType {
    Circle, Square
};

class OVTRigidBody {
private:
    OVTRigidBody(const OVTVector& position, float mass, float density, float restitution, float area, bool isFixed,
                 float radius, float width, float height, ShapeType shape);

public:
    OVTVector m_position;
    OVTVector m_linearVelocity;
    float m_rotationAngle;
    float m_angularVelocity;

    float const m_mass;
    float const m_density;
    float const m_restitution; // Bounciness
    float const m_area;

    bool const m_isFixed; // Does not react to forces

    float const m_radius;
    float const m_width;
    float const m_height;

    ShapeType m_shape;

    void move(const OVTVector& amount);
    void moveTo(const OVTVector& position);

    static OVTRigidBody createCircleBody(float radius, const OVTVector& position, float density, float restitution, bool isFixed);
    static OVTRigidBody createSquareBody(float width, float height, const OVTVector& position, float density, float restitution, bool isFixed);
};


#endif //PHYSICS_ENGINE_OVTRIGIDBODY_H
