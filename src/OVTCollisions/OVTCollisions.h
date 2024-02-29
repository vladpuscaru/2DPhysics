//
// Created by Vlad Puscaru on 29.02.2024.
//

#ifndef PHYSICS_ENGINE_OVTCOLLISIONS_H
#define PHYSICS_ENGINE_OVTCOLLISIONS_H

#include <vector>
#include "../OVTMath/OVTMath.h"
#include "../OVTVector/OVTVector.h"

struct CollisionManifold {
    bool isCollision;
    OVTVector normal;
    float depth;
};

struct VerticesProjectionManifold {
    float min;
    float max;
};

class OVTCollisions {
private:

    static VerticesProjectionManifold projectVertices(const std::vector<OVTVector>& vertices, const OVTVector& axis);

public:
    static CollisionManifold
    intersectCircle(const OVTVector &centerA, float radiusA, const OVTVector &centerB, float radiusB);

    static CollisionManifold
    intersectPolygons(const std::vector<OVTVector> &verticesA, const std::vector<OVTVector> &verticesB);
};


#endif //PHYSICS_ENGINE_OVTCOLLISIONS_H
