//
// Created by Vlad Puscaru on 28.02.2024.
//

#ifndef PHYSICS_ENGINE_OVTRIGIDBODY_H
#define PHYSICS_ENGINE_OVTRIGIDBODY_H

#include "../OVTVector/OVTVector.h"
#include "../OVTMath/OVTMath.h"

#include <iostream>
#include <vector>
#include <cmath>

enum ShapeType {
    Circle, Square
};

class OVTRigidBody {
private:
    static int BODY_COUNT;

    std::vector<OVTVector> m_vertices;
    std::vector<int> m_triangles;
    std::vector<OVTVector> m_transformedVertices;

    bool m_transformUpdateRequired = false;

    std::vector<OVTVector> computeSquareVertices() const;
    std::vector<int> computeSquareTriangles() const;

    OVTRigidBody(const OVTVector& position, float mass, float density, float restitution, float area, bool isFixed,
                 float radius, float width, float height, ShapeType shape);

public:
    int m_id;

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

    void step(float deltaTime);

    void move(const OVTVector& amount);
    void moveTo(const OVTVector& position);
    void rotate(float amount);

    static OVTRigidBody createCircleBody(float radius, const OVTVector& position, float density, float restitution, bool isFixed);
    static OVTRigidBody createSquareBody(float width, float height, const OVTVector& position, float density, float restitution, bool isFixed);

    std::vector<OVTVector> getTransformedVertices();
};


#endif //PHYSICS_ENGINE_OVTRIGIDBODY_H
