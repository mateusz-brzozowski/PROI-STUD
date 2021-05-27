#include "../Tools.h"

#include <gtest/gtest.h>

#include <cmath>

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
    EXPECT_NEAR(expected.x, got.x, 1e-6);
    EXPECT_NEAR(expected.y, got.y, 1e-6);

    // 90-degree rotation
    expected = {0.0, 1.0};
    got = Vector2D{1.0, 0.0}.rotate(M_PI_2);
    EXPECT_NEAR(expected.x, got.x, 1e-6);
    EXPECT_NEAR(expected.y, got.y, 1e-6);

    // 180-degree rotation
    expected = {0.0, 1.0};
    got = Vector2D{0.0, -1.0}.rotate(M_PI);
    EXPECT_NEAR(expected.x, got.x, 1e-6);
    EXPECT_NEAR(expected.y, got.y, 1e-6);

    // 360-degree rotation
    expected = {1.0, 1.0};
    got = Vector2D{1.0, 1.0}.rotate(M_PI * 2);
    EXPECT_NEAR(expected.x, got.x, 1e-6);
    EXPECT_NEAR(expected.y, got.y, 1e-6);
}

TEST(Vector2D, normalize) {
    Vector2D v = {0.0, 0.0};
    EXPECT_NEAR(v.normalize().length(), 0.0, 1e-6);

    v = {1.0, 0.0};
    EXPECT_NEAR(v.normalize().length(), 1.0, 1e-6);

    v = {42.0, -15.0};
    EXPECT_NEAR(v.normalize().length(), 1.0, 1e-6);
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
