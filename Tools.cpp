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

Vector2D& Vector2D::rotate(double angle) {
    double old_x = x;
    double angle_sin = std::sin(angle);
    double angle_cos = std::cos(angle);

    x = x * angle_cos - y * angle_sin;
    y = old_x * angle_sin + y * angle_cos;
    return *this;
}

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
