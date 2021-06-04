#pragma once
#include <SDL.h>

#include <array>

#define CLAMP(v, l, h) ((v) < (l)) ? (l) : ((v) > (h)) ? (h) : (v)

struct Vector2D {
    double x, y;
    Vector2D operator-(Vector2D const&) const;
    Vector2D operator+(Vector2D const&) const;
    Vector2D& operator+=(Vector2D const&);
    Vector2D operator*(double) const;
    double length() const;
    Vector2D& rotate(double angle);
    Vector2D& normalize();
    double distance(Vector2D const&) const;
    double dot(Vector2D const&) const;
};

Vector2D project_points(std::array<Vector2D, 4> const& points,
                        Vector2D const& axis);
bool intervals_overlap(Vector2D const&, Vector2D const&);

class RotatedRect {
   public:
    Vector2D m_center;
    double m_width_half, m_height_half;
    double m_angle;

    RotatedRect(Vector2D center, double width_half, double height_half,
                double angle = 0)
        : m_center(std::move(center)),
          m_width_half(width_half),
          m_height_half(height_half),
          m_angle(angle) {}

    std::array<Vector2D, 4> vertices() const;
    std::array<Vector2D, 2> edge_axes() const;
    Vector2D project(Vector2D const& axis) const;
    bool collides(RotatedRect const&) const;

    void update_sdl_rect_position(SDL_Rect*) const;
    inline double angle_deg() const { return m_angle * 180 / M_PI; }
};
