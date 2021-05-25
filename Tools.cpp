#include "Tools.h"

#include <cmath>

Vector2D Vector2D::operator-(Vector2D const& other) const {
    return {x - other.x, y - other.y};
}

Vector2D Vector2D::operator+(Vector2D const& other) const {
    return {x + other.x, y + other.y};
}

Vector2D& Vector2D::operator+=(Vector2D const& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2D Vector2D::operator*(double scalar) const {
    return {x * scalar, y * scalar};
}

double Vector2D::length() const { return sqrt(x * x + y * y); }

void Vector2D::normalize() {
    double tmp_length = length();
    if (tmp_length > 0) {
        x /= tmp_length;
        y /= tmp_length;
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
