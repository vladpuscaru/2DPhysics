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
