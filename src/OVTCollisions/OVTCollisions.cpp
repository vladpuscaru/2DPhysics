//
// Created by Vlad Puscaru on 29.02.2024.
//

#include "OVTCollisions.h"

/**
 * The normal is oriented towards B
 * @param centerA
 * @param radiusA
 * @param centerB
 * @param radiusB
 * @return
 */
CollisionManifold
OVTCollisions::intersectCircle(const OVTVector &centerA, float radiusA, const OVTVector &centerB, float radiusB) {
    CollisionManifold manifold;
    manifold.isCollision = false;
    manifold.depth = 0.0f;
    manifold.normal = OVTVector::zero();

    float centerDistance = OVTMath::distance(centerA, centerB);
    if (centerDistance < radiusA + radiusB) {
        manifold.isCollision = true;
        manifold.depth = radiusA + radiusB - centerDistance;
        manifold.normal = OVTMath::normalize(centerB - centerA);
    }

    return manifold;
}

/**
 * Separate-Axis Collision Detection
 * @param verticesA
 * @param verticesB
 * @return
 */
CollisionManifold
OVTCollisions::intersectPolygons(const std::vector<OVTVector> &verticesA, const std::vector<OVTVector> &verticesB) {
    CollisionManifold manifold;
    manifold.depth = 0.f;
    manifold.normal = OVTVector::zero();
    manifold.isCollision = true;

    for (int i = 0; i < verticesA.size(); i++) {
        OVTVector vA = verticesA[i];
        OVTVector vB = verticesA[(i + 1) % verticesA.size()]; // Loops back to first element

        OVTVector edge = vB - vA;
        OVTVector axis{-edge.y, edge.x}; // The normal to the edge

        VerticesProjectionManifold projectionManifoldA = projectVertices(verticesA, axis);
        VerticesProjectionManifold projectionManifoldB = projectVertices(verticesB, axis);

        if (projectionManifoldA.min >= projectionManifoldB.max || projectionManifoldB.min >= projectionManifoldA.max) {
            // There is a gap => no collision
            manifold.depth = 0.f;
            manifold.normal = OVTVector::zero();
            manifold.isCollision = false;
            break;
        }
    }

    for (int i = 0; i < verticesB.size(); i++) {
        OVTVector vA = verticesB[i];
        OVTVector vB = verticesB[(i + 1) % verticesB.size()]; // Loops back to first element

        OVTVector edge = vB - vA;
        OVTVector axis{-edge.y, edge.x}; // The normal to the edge

        VerticesProjectionManifold projectionManifoldA = projectVertices(verticesA, axis);
        VerticesProjectionManifold projectionManifoldB = projectVertices(verticesB, axis);

        if (projectionManifoldA.min >= projectionManifoldB.max || projectionManifoldB.min >= projectionManifoldA.max) {
            // There is a gap => no collision
            manifold.depth = 0.f;
            manifold.normal = OVTVector::zero();
            manifold.isCollision = false;
            break;
        }
    }

    return manifold;
}

VerticesProjectionManifold
OVTCollisions::projectVertices(const std::vector<OVTVector> &vertices, const OVTVector &axis) {
    VerticesProjectionManifold manifold{};
    manifold.min = -1;
    manifold.max = -1;
    for (int i = 0; i < vertices.size(); i++) {
        float projection = OVTMath::dot(vertices[i], axis);

        if (i == 0) {
            manifold.min = projection;
            manifold.max = projection;
        } else {
            if (manifold.min > projection) {
                manifold.min = projection;
            }

            if (manifold.max < projection) {
                manifold.max = projection;
            }
        }
    }

    return manifold;
}
