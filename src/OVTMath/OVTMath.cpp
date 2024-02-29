//
// Created by Vlad Puscaru on 28.02.2024.
//

#include "OVTMath.h"

float OVTMath::length(const OVTVector &vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

float OVTMath::distance(const OVTVector &vecA, const OVTVector &vecB) {
    float dx = vecA.x - vecB.x;
    float dy = vecA.y - vecB.y;
    return std::sqrt(dx * dx + dy * dy);
}

OVTVector OVTMath::normalize(const OVTVector &vec) {
    return vec / length(vec);
}

float OVTMath::dot(const OVTVector &vecA, const OVTVector &vecB) {
    return vecA.x * vecB.x + vecA.y * vecB.y;
}

float OVTMath::cross(const OVTVector &vecA, const OVTVector &vecB) {
    return vecA.x * vecB.y - vecA.y * vecB.x;
}

OVTVector OVTMath::transform(const OVTVector &vec, const OVTTransform &transform) {
    OVTVector transformed;

    // Rotate first, then translate
    transformed.x = vec.x * transform.m_cos - vec.y * transform.m_sin;
    transformed.y = vec.x * transform.m_sin - vec.y * transform.m_cos;

    transformed.x += transform.m_x;
    transformed.y += transform.m_y;

    return transformed;
}
