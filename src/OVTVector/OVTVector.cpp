//
// Created by Vlad Puscaru on 28.02.2024.
//

#include "OVTVector.h"

OVTVector::OVTVector(float x, float y)
        : x(x), y(y) {

}

OVTVector OVTVector::operator+(const OVTVector &that) const {
    return {this->x + that.x, this->y + that.y};
}

OVTVector OVTVector::operator*(float scalar) const {
    return {this->x * scalar, this->y * scalar};
}

OVTVector &OVTVector::operator+=(const OVTVector &that) {
    this->x += that.x;
    this->y += that.y;
    return *this;
}

OVTVector OVTVector::operator-(const OVTVector &that) const {
    return *this + (-that)
}

OVTVector OVTVector::operator-() const {
    return {-this->x, -this->y};
}

OVTVector &OVTVector::operator-=(const OVTVector &that) {
    this->x -= that.x;
    this->y -= that.y;
    return *this;
}

OVTVector OVTVector::operator/(float scalar) const {
    return *this * (1 / scalar);
}
