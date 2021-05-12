#include "../Tools.h"

#include <gtest/gtest.h>

#include <cmath>

TEST(rotate_vector, none) {
    Vector2D expected{1.0, 0.0};
    Vector2D got = rotate_vector({1.0, 0.0}, 0.0);
    EXPECT_NEAR(expected.x, got.x, 1e-6);
    EXPECT_NEAR(expected.y, got.y, 1e-6);
}

TEST(rotate_vector, quarter) {
    Vector2D expected{0.0, 1.0};
    Vector2D got = rotate_vector({1.0, 0.0}, M_PI / 2);
    EXPECT_NEAR(expected.x, got.x, 1e-6);
    EXPECT_NEAR(expected.y, got.y, 1e-6);
}

TEST(rotate_vector, half) {
    Vector2D expected{0.0, 1.0};
    Vector2D got = rotate_vector({0.0, -1.0}, M_PI);
    EXPECT_NEAR(expected.x, got.x, 1e-6);
    EXPECT_NEAR(expected.y, got.y, 1e-6);
}

TEST(rotate_vector, full) {
    Vector2D expected{1.0, 1.0};
    Vector2D got = rotate_vector({1.0, 1.0}, M_PI * 2);
    EXPECT_NEAR(expected.x, got.x, 1e-6);
    EXPECT_NEAR(expected.y, got.y, 1e-6);
}
