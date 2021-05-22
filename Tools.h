#pragma once

#define CLAMP(v, l, h) ((v) < (l)) ? (l) : ((v) > (h)) ? (h) : (v)

typedef struct Vector2D{
    double x, y;
    Vector2D operator-(const Vector2D& vector);
    Vector2D operator+(const Vector2D& vector);
    Vector2D operator*(double value);
    double length();
    void normalize();
} Vector2D;

double distance(const Vector2D& vec1, const Vector2D& vec2);
Vector2D rotate_vector(Vector2D vec, double angle);
