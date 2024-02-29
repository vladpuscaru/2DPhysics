//
// Created by Vlad Puscaru on 29.02.2024.
//

#ifndef PHYSICS_ENGINE_OVTTRANSFORM_H
#define PHYSICS_ENGINE_OVTTRANSFORM_H

#include "../OVTVector/OVTVector.h"
#include <cmath>

class OVTTransform {
public:
    float m_x;
    float m_y;
    float m_sin;
    float m_cos;

    OVTTransform(const OVTVector& position, float angle);
    OVTTransform(float x, float y, float angle);

    static OVTTransform zero();
};


#endif //PHYSICS_ENGINE_OVTTRANSFORM_H
