#include "Tools.h"

#include <cmath>
#include <limits>

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

double Vector2D::dot(Vector2D const& other) const {
    return x * other.x + y * other.y;
}

Vector2D project_points(std::array<Vector2D, 4> const& points,
                        Vector2D const& axis) {
    Vector2D interval;
    interval.x = std::numeric_limits<double>::infinity();
    interval.y = -std::numeric_limits<double>::infinity();

    for (auto const& point : points) {
        double d = point.dot(axis);
        if (d < interval.x) interval.x = d;
        if (d > interval.y) interval.y = d;
    }

    return interval;
}

bool intervals_overlap(Vector2D const& i1, Vector2D const& i2) {
    return i1.x < i2.x ? i2.x <= i1.y : i1.x <= i2.y;
}

std::array<Vector2D, 4> RotatedRect::vertices() const {
    return {m_center + Vector2D{m_width_half, m_height_half}.rotate(m_angle),
            m_center + Vector2D{m_width_half, -m_height_half}.rotate(m_angle),
            m_center + Vector2D{-m_width_half, m_height_half}.rotate(m_angle),
            m_center + Vector2D{-m_width_half, -m_height_half}.rotate(m_angle)};
}

std::array<Vector2D, 2> RotatedRect::edge_axes() const {
    return {Vector2D{1, 0}.rotate(m_angle), Vector2D{0, 1}.rotate(m_angle)};
}

bool RotatedRect::collides(RotatedRect const& other) const {
    auto points1 = vertices();
    auto axes1 = edge_axes();

    auto points2 = other.vertices();
    auto axes2 = other.edge_axes();

    for (int edgeIdx = 0; edgeIdx < 4; ++edgeIdx) {
        auto axis = edgeIdx < 2 ? axes1[edgeIdx] : axes2[edgeIdx - 2];

        if (!intervals_overlap(project_points(points1, axis),
                               project_points(points2, axis)))
            return false;
    }

    return true;
}

void RotatedRect::update_sdl_rect_position(SDL_Rect* r) const {
    r->x = (int)(m_center.x - m_width_half);
    r->y = (int)(m_center.y - m_height_half);
}
