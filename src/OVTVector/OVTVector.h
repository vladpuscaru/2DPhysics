//
// Created by Vlad Puscaru on 28.02.2024.
//

#ifndef PHYSICS_ENGINE_OVTVECTOR_H
#define PHYSICS_ENGINE_OVTVECTOR_H


class OVTVector {
public:
    float x;
    float y;

    OVTVector();
    OVTVector(float x, float y);
    OVTVector operator-() const;
    OVTVector operator+(const OVTVector &that) const;
    OVTVector operator-(const OVTVector &that) const;
    OVTVector operator*(float scalar) const;
    OVTVector operator/(float scalar) const;
    bool operator==(const OVTVector &that) const;

    OVTVector &operator+=(const OVTVector &that);
    OVTVector &operator-=(const OVTVector &that);
};


#endif //PHYSICS_ENGINE_OVTVECTOR_H
