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
 * Separating Axis Theorem for Collision Detection
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

        // There is intersection when projecting on this axis, continue checking
        if (i == 0) {
            manifold.normal = axis;
            manifold.depth = std::min<float>(projectionManifoldA.max - projectionManifoldB.min,
                                             projectionManifoldB.max - projectionManifoldA.min);
        } else {
            float newDepth = std::min<float>(projectionManifoldA.max - projectionManifoldB.min,
                                             projectionManifoldB.max - projectionManifoldA.min);
            if (newDepth < manifold.depth) {
                manifold.normal = axis;
                manifold.depth = newDepth;
            }
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

        float newDepth = std::min<float>(projectionManifoldA.max - projectionManifoldB.min,
                                         projectionManifoldB.max - projectionManifoldA.min);
        if (newDepth < manifold.depth) {
            manifold.normal = axis;
            manifold.depth = newDepth;
        }
    }

    manifold.depth /= OVTMath::length(manifold.normal);
    manifold.normal = OVTMath::normalize(manifold.normal);

    OVTVector centerA = findArithmeticMean(verticesA);
    OVTVector centerB = findArithmeticMean(verticesB);

    OVTVector directionOfNormal = centerB - centerA;

    if (OVTMath::dot(directionOfNormal, manifold.normal) < 0.f) {
        // Pointing in separate direction, need to modify the normal
        manifold.normal = -manifold.normal;
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

OVTVector OVTCollisions::findArithmeticMean(const std::vector<OVTVector> &vertices) {
    float sumX = 0.f;
    float sumY = 0.f;

    for (const auto &vertex: vertices) {
        sumX += vertex.x;
        sumY += vertex.y;
    }

    return {sumX / (float) vertices.size(), sumY / (float) vertices.size()};
}

CollisionManifold OVTCollisions::intersectCirclePolygon(const OVTVector &circleCenter, float circleRadius,
                                                        const std::vector<OVTVector> &verticesPolygon) {
    CollisionManifold manifold;
    manifold.depth = 0.f;
    manifold.normal = OVTVector::zero();
    manifold.isCollision = true;

    // Polygon to circle
    for (int i = 0; i < verticesPolygon.size(); i++) {
        OVTVector vA = verticesPolygon[i];
        OVTVector vB = verticesPolygon[(i + 1) % verticesPolygon.size()]; // Loops back to first element

        OVTVector edge = vB - vA;
        OVTVector axis{-edge.y, edge.x}; // The normal to the edge

        VerticesProjectionManifold projectionManifoldA = projectVertices(verticesPolygon, axis);
        VerticesProjectionManifold projectionManifoldB = projectCircle(circleCenter, circleRadius, axis);

        if (projectionManifoldA.min >= projectionManifoldB.max || projectionManifoldB.min >= projectionManifoldA.max) {
            // There is a gap => no collision
            manifold.depth = 0.f;
            manifold.normal = OVTVector::zero();
            manifold.isCollision = false;
            break;
        }

        // There is intersection when projecting on this axis, continue checking
        if (i == 0) {
            manifold.normal = axis;
            manifold.depth = std::min<float>(projectionManifoldA.max - projectionManifoldB.min,
                                             projectionManifoldB.max - projectionManifoldA.min);
        } else {
            float newDepth = std::min<float>(projectionManifoldA.max - projectionManifoldB.min,
                                             projectionManifoldB.max - projectionManifoldA.min);
            if (newDepth < manifold.depth) {
                manifold.normal = axis;
                manifold.depth = newDepth;
            }
        }
    }

    // Circle to polygon
    OVTVector closestPoint = findClosestPointOnPolygon(circleCenter, verticesPolygon);
    OVTVector axis = closestPoint - circleCenter;

    VerticesProjectionManifold projectionManifoldA = projectVertices(verticesPolygon, axis);
    VerticesProjectionManifold projectionManifoldB = projectCircle(circleCenter, circleRadius, axis);

    if (projectionManifoldA.min >= projectionManifoldB.max || projectionManifoldB.min >= projectionManifoldA.max) {
        // There is a gap => no collision
        manifold.depth = 0.f;
        manifold.normal = OVTVector::zero();
        manifold.isCollision = false;
    }

    float newDepth = std::min<float>(projectionManifoldA.max - projectionManifoldB.min,
                                     projectionManifoldB.max - projectionManifoldA.min);
    if (newDepth < manifold.depth) {
        manifold.normal = axis;
        manifold.depth = newDepth;
    }

    manifold.depth /= OVTMath::length(manifold.normal);
    manifold.normal = OVTMath::normalize(manifold.normal);

    OVTVector centerB = findArithmeticMean(verticesPolygon);

    OVTVector directionOfNormal = centerB - circleCenter;

    if (OVTMath::dot(directionOfNormal, manifold.normal) < 0.f) {
        // Pointing in separate direction, need to modify the normal
        manifold.normal = -manifold.normal;
    }

    return manifold;
}

VerticesProjectionManifold OVTCollisions::projectCircle(const OVTVector &center, float radius, OVTVector &axis) {
    VerticesProjectionManifold manifold{};

    OVTVector direction = OVTMath::normalize(axis);
    OVTVector directionAndRadius = direction * radius;

    OVTVector p1 = center + directionAndRadius;
    OVTVector p2 = center - directionAndRadius;

    manifold.min = OVTMath::dot(p1, axis);
    manifold.max = OVTMath::dot(p2, axis);

    if (manifold.min > manifold.max) {
        float temp = manifold.min;
        manifold.min = manifold.max;
        manifold.max = temp;
    }

    return manifold;
}

OVTVector
OVTCollisions::findClosestPointOnPolygon(const OVTVector &circleCenter, const std::vector<OVTVector> &polygonVertices) {
    int minIdx = -1;
    float minDistance = 0.f;

    for (int i = 0; i < polygonVertices.size(); i++) {
        float distance = OVTMath::distance(circleCenter, polygonVertices[i]);

        if (i == 0 || minDistance > distance) {
            minIdx = i;
            minDistance = distance;
        }
    }

    return polygonVertices[minIdx];
}
