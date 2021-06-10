
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

TEST(AutonomousCar, sensor_collides) {
    GTEST_SKIP() << "AutonomousCar::sensor_collides is a TODO!";
}

TEST(AutonomousCar, update_sensor_pos) {
    GTEST_SKIP() << "AutonomousCar::update_sensor_pos is a TODO!";
}

TEST(AutonomousCar, initialize_sensors) {
    MapNoGui m;
    m.init();

    auto c = std::make_shared<AutonomousCar>(Vector2D{100, 100}, nullptr);
    // m.add() calls c.set_map(), which should call c.initialize_sensors()
    m.add(c);

    auto sensors = c->get_sensors();

    ASSERT_EQ(sensors.size(), 5);

    // Front sensor
    EXPECT_VECTOR_NEAR(sensors[0].center_offset, (Vector2D{27, 0}));
    EXPECT_NEAR(sensors[0].angle_offset, 0, 1e-6);
    EXPECT_NEAR(sensors[0].avoid_factor, 1, 1e-6);

    // Right-Front sensor
    EXPECT_VECTOR_NEAR(sensors[1].center_offset, (Vector2D{27, 9}));
    EXPECT_NEAR(sensors[1].angle_offset, 0, 1e-6);
    EXPECT_NEAR(sensors[1].avoid_factor, -1, 1e-6);

    // Right-Corner sensor
    EXPECT_VECTOR_NEAR(sensors[2].center_offset,
                       (Vector2D{21.727922, 21.727922}));
    EXPECT_NEAR(sensors[2].angle_offset, M_PI_4, 1e-6);
    EXPECT_NEAR(sensors[2].avoid_factor, -.5, 1e-6);

    // Left-Front sensor
    EXPECT_VECTOR_NEAR(sensors[3].center_offset, (Vector2D{27, -9}));
    EXPECT_NEAR(sensors[3].angle_offset, 0, 1e-6);
    EXPECT_NEAR(sensors[3].avoid_factor, 1, 1e-6);

    // Left-Corner sensor
    EXPECT_VECTOR_NEAR(sensors[4].center_offset,
                       (Vector2D{21.727922, -21.727922}));
    EXPECT_NEAR(sensors[4].angle_offset, -M_PI_4, 1e-6);
    EXPECT_NEAR(sensors[4].avoid_factor, .5, 1e-6);
}
