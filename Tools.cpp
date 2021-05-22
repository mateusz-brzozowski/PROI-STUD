#include "Tools.h"

#include <cmath>

Vector2D Vector2D::operator-(const Vector2D& vector) { 
    return {x - vector.x, y - vector.y};
}

Vector2D Vector2D::operator+(const Vector2D& vector) {
    return {x + vector.x, y + vector.y};
}

Vector2D Vector2D::operator*(double value) { 
    x *= value;
    y *= value;
    return *this;
}

double Vector2D::length() { 
    return sqrt(pow(x, 2) + pow(y, 2)); 
}

void Vector2D::normalize() {
    double tmp_length = length();
    if (tmp_length > 0) {
        x = x / tmp_length;
        y = y / tmp_length;
    }
}

double distance(const Vector2D& vec1, const Vector2D& vec2) {
    return sqrt(pow(vec1.x - vec2.x, 2) + pow(vec1.y - vec2.y, 2));
}

Vector2D rotate_vector(Vector2D vec, double angle) {
    double sin = std::sin(angle);
    double cos = std::cos(angle);
    return {vec.x * cos - vec.y * sin, vec.x * sin + vec.y * cos};
}
