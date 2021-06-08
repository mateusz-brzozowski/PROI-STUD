#include "../Tools.h"

#include <SDL.h>
#include <gtest/gtest.h>

#include <cmath>

#define EXPECT_VECTOR_NEAR(a, b) EXPECT_TRUE(VectorNear((a), (b)))

testing::AssertionResult VectorNear(Vector2D const v1, Vector2D const v2,
                                    double delta = 1e-6) {
    double dx = std::abs(v1.x - v2.x);
    double dy = std::abs(v1.y - v2.y);

    if (dx > delta || dy > delta) {
        return testing::AssertionFailure()
               << "Vector2D{" << v1.x << ", " << v1.y
               << "} isn't close to Vector2D{" << v2.x << ", " << v2.y << "}";
    }

    return testing::AssertionSuccess();
}

/// TODO: Test project_points()
/// TODO: Test RotatedRect::collides()
/// TODO: Test RotatedRect::update_sdl_rect_position()
/// TODO: Test RotatedRect::angle_deg()

TEST(Clamp, int) {
    EXPECT_EQ(CLAMP(-5, 0, 100), 0);
    EXPECT_EQ(CLAMP(200, 0, 100), 100);
    EXPECT_EQ(CLAMP(50, 0, 100), 50);
}

TEST(Clamp, double) {
    EXPECT_NEAR(CLAMP(-5.0, 0.0, 100.0), 0.0, 1e-6);
    EXPECT_NEAR(CLAMP(-HUGE_VAL, 0.0, 100.0), 0.0, 1e-6);

    EXPECT_NEAR(CLAMP(128, 0.0, 100.0), 100.0, 1e-6);
    EXPECT_NEAR(CLAMP(HUGE_VAL, 0.0, 100.0), 100.0, 1e-6);

    EXPECT_NEAR(CLAMP(12.0, 0.0, 100.0), 12.0, 1e-6);
    EXPECT_NEAR(CLAMP(64.0, 0.0, 100.0), 64.0, 1e-6);
}

TEST(Vector2D, operators) {
    Vector2D v1{0.0, 0.0};
    Vector2D v2{0.0, 0.0};
    Vector2D expected{0.0, 0.0};

    // Adding and subtracting
    EXPECT_VECTOR_NEAR(v1 + v2, expected);
    EXPECT_VECTOR_NEAR(v1 - v2, expected);

    v1 = {1.0, 1.0};
    v2 = {1.0, 1.0};
    EXPECT_VECTOR_NEAR(v1 - v2, expected);

    expected = {2.0, 2.0};
    EXPECT_VECTOR_NEAR(v1 + v2, expected);

    // Adding with assignment
    EXPECT_VECTOR_NEAR(v1 = v1 + v2, expected);
    EXPECT_VECTOR_NEAR(v1, expected);

    // Multiply by scalar
    EXPECT_VECTOR_NEAR(v2 * 2.0, expected);

    expected = {-1.0, -1.0};
    EXPECT_VECTOR_NEAR(v1 * -.5, expected);

    expected = {0.0, 0.0};
    EXPECT_VECTOR_NEAR(v2 * 0.0, expected);
}

TEST(Vector2D, length) {
    Vector2D v = {0.0, 0.0};
    EXPECT_NEAR(v.length(), 0.0, 1e-6);

    v = {0.0, 5.0};
    EXPECT_NEAR(v.length(), 5.0, 1e-6);

    v = {-1.0, -1.0};
    EXPECT_NEAR(v.length(), M_SQRT2, 1e-6);

    v = {-4.0, 3.0};
    EXPECT_NEAR(v.length(), 5.0, 1e-6);
}

TEST(Vector2D, rotate) {
    // Null rotation
    Vector2D expected{1.0, 0.0};
    Vector2D got = Vector2D{1.0, 0.0}.rotate(0.0);
    EXPECT_VECTOR_NEAR(got, expected);

    // 90-degree rotation
    expected = {0.0, 1.0};
    got = Vector2D{1.0, 0.0}.rotate(M_PI_2);
    EXPECT_VECTOR_NEAR(got, expected);

    // 180-degree rotation
    expected = {0.0, 1.0};
    got = Vector2D{0.0, -1.0}.rotate(M_PI);
    EXPECT_VECTOR_NEAR(got, expected);

    // 360-degree rotation
    expected = {1.0, 1.0};
    got = Vector2D{1.0, 1.0}.rotate(M_PI * 2);
    EXPECT_VECTOR_NEAR(got, expected);
}

TEST(Vector2D, normalize) {
    Vector2D got = {0.0, 0.0};
    Vector2D expected = {0.0, 0.0};

    got.normalize();
    EXPECT_VECTOR_NEAR(got, expected);
    EXPECT_NEAR(got.length(), 0.0, 1e-6);

    got = {1.0, 0.0};
    got.normalize();
    expected = {1.0, 0.0};
    EXPECT_NEAR(got.length(), 1.0, 1e-6);
    EXPECT_VECTOR_NEAR(got, expected);

    got = {42.0, -15.0};
    got.normalize();
    expected = {.94174191, -.3363364};
    EXPECT_NEAR(got.length(), 1.0, 1e-6);
    EXPECT_VECTOR_NEAR(got, expected);
}

TEST(Vector2D, distance) {
    Vector2D v1{1.0, 1.0};
    Vector2D v2{1.0, 1.0};

    EXPECT_NEAR(v1.distance(v2), 0.0, 1e-6);

    v1 = {1.0, 2.0};
    EXPECT_NEAR(v1.distance(v2), 1.0, 1e-6);

    v1 = {2.0, 2.0};
    EXPECT_NEAR(v1.distance(v2), M_SQRT2, 1e-6);

    v1 = {-1, -1};
    EXPECT_NEAR(v1.distance(v2), 2 * M_SQRT2, 1e-6);
}

TEST(IntervalsOverlap, normal) {
    EXPECT_TRUE(intervals_overlap({1, 3}, {2, 4}));
    EXPECT_TRUE(intervals_overlap({2, 4}, {1, 3}));
    EXPECT_TRUE(intervals_overlap({-5, 5}, {-10, -2}));
    EXPECT_TRUE(intervals_overlap({5, 5}, {0, 5}));

    EXPECT_FALSE(intervals_overlap({1, 3}, {4, 6}));
    EXPECT_FALSE(intervals_overlap({-5, -2}, {-1, 5}));
}

TEST(RotatedRect, vertices) {
    auto points = RotatedRect({2, 2}, 1, 1, 0).vertices();
    EXPECT_TRUE(VectorNear(points[0], {3, 3}));
    EXPECT_TRUE(VectorNear(points[1], {3, 1}));
    EXPECT_TRUE(VectorNear(points[2], {1, 1}));
    EXPECT_TRUE(VectorNear(points[3], {1, 3}));

    points = RotatedRect({2, 2}, 1, 1, M_PI_4).vertices();
    EXPECT_TRUE(VectorNear(points[0], {2, 3.41421356}));
    EXPECT_TRUE(VectorNear(points[1], {3.41421356, 2}));
    EXPECT_TRUE(VectorNear(points[2], {2, 0.58578644}));
    EXPECT_TRUE(VectorNear(points[3], {0.58578644, 2}));
}

TEST(RotatedRect, edge_axes) {
    auto edge_axes = RotatedRect({2, 2}, 1, 1, 0).edge_axes();
    EXPECT_TRUE(VectorNear(edge_axes[0], {1, 0}));
    EXPECT_TRUE(VectorNear(edge_axes[1], {0, 1}));

    edge_axes = RotatedRect({2, 2}, 1, 1, M_PI_4).edge_axes();
    EXPECT_TRUE(VectorNear(edge_axes[0], {.70710678, .70710678}));
    EXPECT_TRUE(VectorNear(edge_axes[1], {-.70710678, .70710678}));
}
