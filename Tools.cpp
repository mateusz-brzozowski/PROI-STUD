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

Vector2D& Vector2D::normalize() {
    double tmp_length = length();
    if (tmp_length > 0) {
        x /= tmp_length;
        y /= tmp_length;
    }
    return *this;
}

double Vector2D::distance(Vector2D const& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return sqrt(dx * dx + dy * dy);
}

bool CollisionAABB(const SDL_Rect* recA, const SDL_Rect* recB) {
    return recA->x + recA->w >= recB->x && recB->x + recB->w >= recA->x &&
           recA->y + recA->h >= recB->y && recB->y + recB->h >= recA->y;
}