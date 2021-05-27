#pragma once

#define CLAMP(v, l, h) ((v) < (l)) ? (l) : ((v) > (h)) ? (h) : (v)

typedef struct Vector2D {
    double x, y;
    Vector2D operator-(Vector2D const&) const;
    Vector2D operator+(Vector2D const&) const;
    Vector2D& operator+=(Vector2D const&);
    Vector2D operator*(double) const;
    double length() const;
    Vector2D& rotate(double angle);
    Vector2D& normalize();
    double distance(Vector2D const&) const;
} Vector2D;
