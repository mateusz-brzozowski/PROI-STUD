#include "../Tools.h"

#include <gtest/gtest.h>

#include <cmath>

/** Vector Rotation */

TEST(vector_rotate, none) {
    Vector2D expected{1.0, 0.0};
    Vector2D got = Vector2D{1.0, 0.0}.rotate(0.0);
    EXPECT_NEAR(expected.x, got.x, 1e-6);
    EXPECT_NEAR(expected.y, got.y, 1e-6);
}

TEST(vector_rotate, quarter) {
    Vector2D expected{0.0, 1.0};
    Vector2D got = Vector2D{1.0, 0.0}.rotate(M_PI / 2);
    EXPECT_NEAR(expected.x, got.x, 1e-6);
    EXPECT_NEAR(expected.y, got.y, 1e-6);
}

TEST(vector_rotate, half) {
    Vector2D expected{0.0, 1.0};
    Vector2D got = Vector2D{0.0, -1.0}.rotate(M_PI);
    EXPECT_NEAR(expected.x, got.x, 1e-6);
    EXPECT_NEAR(expected.y, got.y, 1e-6);
}

TEST(vector_rotate, full) {
    Vector2D expected{1.0, 1.0};
    Vector2D got = Vector2D{1.0, 1.0}.rotate(M_PI * 2);
    EXPECT_NEAR(expected.x, got.x, 1e-6);
    EXPECT_NEAR(expected.y, got.y, 1e-6);
}
