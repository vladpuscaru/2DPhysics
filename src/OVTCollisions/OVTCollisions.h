//
// Created by Vlad Puscaru on 29.02.2024.
//

#ifndef PHYSICS_ENGINE_OVTCOLLISIONS_H
#define PHYSICS_ENGINE_OVTCOLLISIONS_H

#include "../OVTMath/OVTMath.h"
#include "../OVTVector/OVTVector.h"

struct CollisionManifold {
    bool isCollision;
    OVTVector normal;
    float depth;
};

class OVTCollisions {
public:
    static CollisionManifold intersectCircle(const OVTVector& centerA, float radiusA, const OVTVector& centerB, float radiusB);
};


#endif //PHYSICS_ENGINE_OVTCOLLISIONS_H
