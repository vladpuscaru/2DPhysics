//
// Created by Vlad Puscaru on 28.02.2024.
//

#ifndef PHYSICS_ENGINE_OVTMATH_H
#define PHYSICS_ENGINE_OVTMATH_H

#include "../OVTVector/OVTVector.h"
#include <cmath>

class OVTMath {
public:
    static float length(const OVTVector &vec);
    static float distance(const OVTVector &vecA, const OVTVector &vecB);
    static OVTVector normalize(const OVTVector &vec);
    static float dot(const OVTVector &vecA, const OVTVector &vecB);
    static float cross(const OVTVector &vecA, const OVTVector &vecB);
};


#endif //PHYSICS_ENGINE_OVTMATH_H
