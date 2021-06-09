
#include "../Car.h"

#include <gtest/gtest.h>

#include <memory>

#include "../Map.h"
#include "../Object.h"

#define EXPECT_VECTOR_NEAR(a, b) EXPECT_TRUE(VectorNear((a), (b)))

extern testing::AssertionResult VectorNear(Vector2D const v1, Vector2D const v2,
                                           double delta = 1e-6);
// Defined in tools.cpp

TEST(Car, validate_new_position) {
    // Objects for checking
    MapNoGui m;
    m.init();

    auto c = std::make_shared<Car>(Vector2D{50, 50}, 1.5);
    m.add(c);

    // Valid new position
    EXPECT_TRUE(c->validate_new_position({100, 100}));
    EXPECT_VECTOR_NEAR(c->get_bbox()->m_center, (Vector2D{100, 100}));

    // Too close to the map bound - check clamping
    EXPECT_TRUE(c->validate_new_position({5, 100}));
    EXPECT_VECTOR_NEAR(c->get_bbox()->m_center, (Vector2D{9, 100}));

    // Collisions
    m.add(new Bush({120, 120}));
    EXPECT_FALSE(c->validate_new_position({100, 100}));
    EXPECT_VECTOR_NEAR(c->get_bbox()->m_center, (Vector2D{9, 100}));
}

TEST(Car, update) {
    // Objects for checking
    MapNoGui m;
    m.init();

    auto c = std::make_shared<Car>(Vector2D{400, 400}, M_PI);
    m.add(c);

    // No buttons pressed
    for (int i = 10; i != 0; --i) m.update();
    EXPECT_VECTOR_NEAR(c->get_bbox()->m_center, (Vector2D{400, 400}));

    // Forward (towards negative x)
    m.set_pressed_keys(KEY_W);
    for (int i = 10; i != 0; --i) m.update();
    EXPECT_VECTOR_NEAR(c->get_bbox()->m_center, (Vector2D{350, 400}));

    // Backwards (towards positive x)
    m.set_pressed_keys(KEY_S);
    for (int i = 10; i != 0; --i) m.update();
    EXPECT_VECTOR_NEAR(c->get_bbox()->m_center, (Vector2D{400, 400}));

    // Rotate right (angle increasing)
    m.set_pressed_keys(KEY_D);
    for (int i = 10; i != 0; --i) m.update();
    EXPECT_NEAR(c->get_bbox()->m_angle, M_PI + 1, 1e-6);

    // Rotate Left (angle decreasing)
    m.set_pressed_keys(KEY_A);
    for (int i = 10; i != 0; --i) m.update();
    EXPECT_NEAR(c->get_bbox()->m_angle, M_PI, 1e-6);
}
