//
// Created by Vlad Puscaru on 28.02.2024.
//

#include "OVTRigidBody.h"
#include "../OVTWorld/OVTWorld.h"

int OVTRigidBody::BODY_COUNT = 1;

OVTRigidBody::OVTRigidBody(const OVTVector &position, float mass, float density, float restitution, float area,
                           bool isFixed,
                           float radius, float width, float height, ShapeType shape)
        : m_id(OVTRigidBody::BODY_COUNT++), m_position(position), m_mass(mass), m_density(density), m_restitution(restitution), m_area(area),
          m_isFixed(isFixed), m_radius(radius), m_width(width), m_height(height), m_shape(shape) {
    m_linearVelocity = OVTVector::zero();
    m_rotationAngle = 0.0f;
    m_angularVelocity = 0.0f;

    m_transformUpdateRequired = true;

    if (m_shape == ShapeType::Square) {
        m_vertices = computeSquareVertices();
        m_transformedVertices = {};
        m_triangles = computeSquareTriangles();
    }
}

OVTRigidBody OVTRigidBody::createCircleBody(float radius, const OVTVector &position, float density, float restitution,
                                            bool isFixed) {
    if (density < OVTWorld::MIN_DENSITY || density > OVTWorld::MAX_DENSITY) {
        std::cerr << "ERROR::RIGID_BODY::CIRCLE_CREATION"
                  << " Density " << density << " outside of range "
                  << "(" << OVTWorld::MIN_DENSITY << ", " << OVTWorld::MAX_DENSITY << ")"
                  << std::endl;
        exit(-1);
    }

    float area = radius * radius * M_PI;

    if (area < OVTWorld::MIN_BODY_SIZE || area > OVTWorld::MAX_BODY_SIZE) {
        std::cerr << "ERROR::RIGID_BODY::CIRCLE_CREATION"
                  << " Calculated body size(area) " << area << " from radius " << radius << " outside of range "
                  << "(" << OVTWorld::MIN_BODY_SIZE << ", " << OVTWorld::MAX_BODY_SIZE << ")"
                  << std::endl;
        exit(-1);
    }

    restitution = std::clamp<float>(restitution, 0, 1);

    float mass = density * area;

    return OVTRigidBody(position, mass, density, restitution, area, isFixed, radius, 0.0f, 0.0f, ShapeType::Circle);
}

OVTRigidBody
OVTRigidBody::createSquareBody(float width, float height, const OVTVector &position, float density, float restitution,
                               bool isFixed) {
    if (density < OVTWorld::MIN_DENSITY || density > OVTWorld::MAX_DENSITY) {
        std::cerr << "ERROR::RIGID_BODY::CIRCLE_CREATION"
                  << " Density " << density << " outside of range "
                  << "(" << OVTWorld::MIN_DENSITY << ", " << OVTWorld::MAX_DENSITY << ")"
                  << std::endl;
        exit(-1);
    }

    float area = width * height;

    if (area < OVTWorld::MIN_BODY_SIZE || area > OVTWorld::MAX_BODY_SIZE) {
        std::cerr << "ERROR::RIGID_BODY::CIRCLE_CREATION"
                  << " Calculated body size(area) " << area << " from width " << width << " and height " << height
                  << " outside of range "
                  << "(" << OVTWorld::MIN_BODY_SIZE << ", " << OVTWorld::MAX_BODY_SIZE << ")"
                  << std::endl;
        exit(-1);
    }

    restitution = std::clamp<float>(restitution, 0, 1);

    float mass = density * area;

    return OVTRigidBody(position, mass, density, restitution, area, isFixed, 0.0f, width, height, ShapeType::Square);
}

void OVTRigidBody::move(const OVTVector &amount) {
    m_position += amount;
    m_transformUpdateRequired = true;
}

void OVTRigidBody::moveTo(const OVTVector &position) {
    m_position = position;
    m_transformUpdateRequired = true;
}

std::vector<OVTVector> OVTRigidBody::computeSquareVertices() const {
    if (m_shape != ShapeType::Square)
        return {};

    // Clockwise vertices, starting from top-left

    float left = -m_width / 2.f;
    float right = left + m_width;
    float bottom = -m_height / 2.f;
    float top = bottom + m_height;

    return {
            OVTVector{left, top},
            OVTVector{right, top},
            OVTVector{right, bottom},
            OVTVector{left, bottom},
    };
}

std::vector<int> OVTRigidBody::computeSquareTriangles() const {
    if (m_shape != ShapeType::Square)
        return {};

    return {
            0, 1, 2, 0, 2, 3
    };
}

void OVTRigidBody::rotate(float amount) {
    m_rotationAngle += amount;
    m_transformUpdateRequired = true;
}

std::vector<OVTVector> OVTRigidBody::getTransformedVertices() {
    if (m_transformUpdateRequired) {
        m_transformedVertices.clear();

        OVTTransform transform {m_position, m_rotationAngle};
        for (auto& vertex : m_vertices) {
            OVTVector transformedVertex = OVTMath::transform(vertex, transform);
            m_transformedVertices.push_back(transformedVertex);
        }

        m_transformUpdateRequired = false;
    }

    return m_transformedVertices;
}

void OVTRigidBody::step(float deltaTime) {
    m_position += m_linearVelocity * deltaTime;
    m_rotationAngle += m_angularVelocity * deltaTime;
}
