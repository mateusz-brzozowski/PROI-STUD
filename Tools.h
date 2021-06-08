#pragma once
#include <SDL.h>

#include <vector>

#define CLAMP(v, l, h) ((v) < (l)) ? (l) : ((v) > (h)) ? (h) : (v)

/**
 * Vector2D represents a pair of 2 numbers, aka a 2D vector.
 */
struct Vector2D {
    double x, y;

    /// Subtract one vector from another
    Vector2D operator-(Vector2D const&) const;
    /// Add two vectors together
    Vector2D operator+(Vector2D const&) const;
    /// Multiply a vector by a scalar
    Vector2D operator*(double) const;
    /// Calculate the length of a vector
    double length() const;
    /// Rotate this vector by some angle (in radians)
    Vector2D& rotate(double angle);
    /// Returns a new vector as a result of rotating this vector by some angle
    Vector2D rotated(double angle) const;
    /// Normalize the vector, so that its length is 1.
    Vector2D& normalize();
    /// Euclidian distance between 2 points
    double distance(Vector2D const&) const;
    /// Calculate the dot product of 2 vectors
    double dot(Vector2D const&) const;
};

/**
 * Projects points onto an axis.
 * @returns an interval from the smallest value (x) to the biggest value (y)
 * after projecting all of the points
 */
Vector2D project_points(std::vector<Vector2D> const& points,
                        Vector2D const& axis);

/**
 * Checks if 2 intervals overlap.
 * x attributes are understood as the lower bound of an interval,
 * and y attributes as the upper bound.
 */
bool intervals_overlap(Vector2D const&, Vector2D const&);

/**
 * RotatedRect is a class used to represent a rectangle on a plane,
 * that can be rotated by any angle.
 */
class RotatedRect {
   public:
    /// Center point of the rectangle
    Vector2D m_center;
    /// Size of the rectangle
    double m_width_half, m_height_half;
    /// Rotation angle of the rectangle (in radians)
    double m_angle;

    /**
     * Create a RotatedRect
     * @param center center point of the rectangle
     * @param width_half half of the width of the rectangle
     * @param height_half half of the height of the rectangle
     * @param angle rotation of the rectangle (from the center point, in
     * radians)
     */
    RotatedRect(Vector2D center = {0, 0}, double width_half = 0,
                double height_half = 0, double angle = 0)
        : m_center(std::move(center)),
          m_width_half(width_half),
          m_height_half(height_half),
          m_angle(angle) {}

    /**
     * Get coordinates of all of this rectangle's
     * verticies
     */
    std::vector<Vector2D> vertices() const;

    /**
     * Get all axes (normalized) parallel to all of the edges
     * of this rectangle.
     */
    std::vector<Vector2D> edge_axes() const;

    /**
     * Check if a given rectangle collides with a
     * different rectnagle.
     */
    bool collides(RotatedRect const&) const;

    /**
     * Updates the `x` and `y` attributes of an SDL_Rect;
     * ignoring any rotation
     */
    void update_sdl_rect_position(SDL_Rect*) const;

    /**
     * Returns the rotation angle in degrees
     */
    inline double angle_deg() const { return m_angle * 180 / M_PI; }
};
