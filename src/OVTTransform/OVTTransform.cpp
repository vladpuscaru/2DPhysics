//
// Created by Vlad Puscaru on 29.02.2024.
//

#include "OVTTransform.h"

OVTTransform::OVTTransform(float x, float y, float angle)
        : m_x(x), m_y(y), m_sin(std::sin(angle)), m_cos(std::cos(angle)) {

}

OVTTransform::OVTTransform(const OVTVector &position, float angle)
        : OVTTransform(position.x, position.y, angle) {

}

OVTTransform OVTTransform::zero() {
    return OVTTransform(OVTVector::zero(), 0.f);
}
