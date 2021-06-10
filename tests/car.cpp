
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

// Expose internal functions from AutonomousCar

class ExposedAutonomousCar : public AutonomousCar {
   public:
    using AutonomousCar::AutonomousCar;
    RotatedRect const* sensor_collides(Sensor const& s) const {
        return AutonomousCar::sensor_collides(s);
    }

    void update_sensor_pos() { AutonomousCar::update_sensor_pos(); }
    void initialize_sensors() { AutonomousCar::initialize_sensors(); }
    RotatedRect& get_modifiable_bbox() { return m_position; }
};

TEST(AutonomousCar, sensor_collides) {
    MapNoGui m;
    m.init();

    auto c = std::make_shared<ExposedAutonomousCar>(Vector2D{9, 9}, nullptr);
    m.add(c);

    auto o = std::make_shared<Bush>(Vector2D{36, 36});
    m.add(o);

    c->update_sensor_pos();

    auto& sensors = c->get_sensors();

    EXPECT_EQ(c->sensor_collides(sensors[0]), nullptr);
    EXPECT_EQ(c->sensor_collides(sensors[1]), nullptr);
    EXPECT_EQ(c->sensor_collides(sensors[2]), o->get_bbox());
    EXPECT_EQ(c->sensor_collides(sensors[3]), nullptr);
    EXPECT_EQ(c->sensor_collides(sensors[4]), nullptr);
}

TEST(AutonomousCar, update_sensor_pos) {
    ExposedAutonomousCar c{Vector2D{100, 100}, nullptr};

    auto& bbox = c.get_modifiable_bbox();
    bbox.m_width_half = 9;
    bbox.m_height_half = 9;
    bbox.m_angle = M_PI_4;

    c.initialize_sensors();
    c.update_sensor_pos();
    auto& sensors = c.get_sensors();

    ASSERT_EQ(sensors.size(), 5);

    // Front sensor
    EXPECT_VECTOR_NEAR(sensors[0].bbox.m_center,
                       (Vector2D{119.091883, 119.091883}));
    EXPECT_NEAR(sensors[0].bbox.m_angle, M_PI_4, 1e-6);

    // Right-Front sensor
    EXPECT_VECTOR_NEAR(sensors[1].bbox.m_center,
                       (Vector2D{112.727922, 125.455844}));
    EXPECT_NEAR(sensors[1].bbox.m_angle, M_PI_4, 1e-6);

    // Right-Corner sensor
    EXPECT_VECTOR_NEAR(sensors[2].bbox.m_center, (Vector2D{100, 130.727922}));
    EXPECT_NEAR(sensors[2].bbox.m_angle, M_PI_2, 1e-6);

    // Left-Front sensor
    EXPECT_VECTOR_NEAR(sensors[3].bbox.m_center,
                       (Vector2D{125.455844, 112.727922}));
    EXPECT_NEAR(sensors[3].bbox.m_angle, M_PI_4, 1e-6);

    // Left-Corner sensor
    EXPECT_VECTOR_NEAR(sensors[4].bbox.m_center, (Vector2D{130.727922, 100}));
    EXPECT_NEAR(sensors[4].bbox.m_angle, 0, 1e-6);
}

TEST(AutonomousCar, initialize_sensors) {
    ExposedAutonomousCar c{Vector2D{100, 100}, nullptr};

    auto& bbox = c.get_modifiable_bbox();
    bbox.m_width_half = 9;
    bbox.m_height_half = 9;

    c.initialize_sensors();
    auto& sensors = c.get_sensors();

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
