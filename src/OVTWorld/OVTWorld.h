//
// Created by Vlad Puscaru on 28.02.2024.
//

#ifndef PHYSICS_ENGINE_OVTWORLD_H
#define PHYSICS_ENGINE_OVTWORLD_H

#include "../OVTRigidBody/OVTRigidBody.h"

class OVTWorld {
private:
    OVTRigidBody body;
public:
    constexpr static const float MIN_BODY_SIZE = 0.01f * 0.01f;
    constexpr static const float MAX_BODY_SIZE = 64.0f * 64.0f;

    constexpr static const float MIN_DENSITY = 0.2f; // g / cm3
    constexpr static const float MAX_DENSITY = 21.4f; // g / cm3
};


#endif //PHYSICS_ENGINE_OVTWORLD_H
