#pragma once

#define CLAMP(v, l, h) ((v) < (l)) ? (l) : ((v) > (h)) ? (h) : (v)

typedef struct {
    double x, y;
} Vector2D;

Vector2D rotate_vector(Vector2D vec, double angle);
