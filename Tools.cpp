#include "Tools.h"

#include <cmath>

Vector2D rotate_vector(Vector2D vec, double angle) {
    double sin = std::sin(angle);
    double cos = std::cos(angle);
    return {vec.x * cos - vec.y * sin, vec.x * sin + vec.y * cos};
}
