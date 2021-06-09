#include <gtest/gtest.h>

#include "../Car.h"
#include "../Map.h"
#include "../Object.h"

TEST(Autonomy, no_obstacles) {
    // Prepare the map
    MapNoGui m;
    m.init();

    // Add the target Car and an Autonomous vehicle
    auto main_car = new Car({700, 300});
    auto autonomous_car = new AutonomousCar({200, 300}, main_car);
    m.add(main_car);
    m.add(autonomous_car);

    // Calculate how many iterations it takes
    // to reach the target
    int iterations = 0;

    for (; iterations < 1500; ++iterations) {
        m.update();
        if (main_car->get_bbox()->m_center.distance(
                autonomous_car->get_bbox()->m_center) < 30)
            break;
    }

    EXPECT_NEAR(iterations, 470, 20);
}

TEST(Autonomy, simple_obstacle) {
    // Prepare the map
    MapNoGui m;
    m.init();

    // Add the target Car and an Autonomous vehicle
    auto main_car = new Car({700, 300});
    auto autonomous_car = new AutonomousCar({200, 300}, main_car);
    m.add(main_car);
    m.add(autonomous_car);

    // Add obstacles
    m.add(new Lake({232, 220}));
    m.add(new Lake({232, 380}));
    m.add(new Bus({280, 268}));
    m.add(new Bus({280, 332}));

    int iterations = 0;

    for (; iterations < 1500; ++iterations) {
        m.update();
        if (main_car->get_bbox()->m_center.distance(
                autonomous_car->get_bbox()->m_center) <= 30)
            break;
    }

    EXPECT_NEAR(iterations, 650, 20);
}

TEST(Autonomy, no_way_out) {
    // Prepare the map
    MapNoGui m;
    m.init();

    // Add the target Car and an Autonomous vehicle
    auto main_car = new Car({700, 300});
    auto autonomous_car = new AutonomousCar({200, 300}, main_car);
    m.add(main_car);
    m.add(autonomous_car);

    // Add obstacles
    m.add(new Lake({232, 220}));
    m.add(new Lake({232, 380}));
    m.add(new Bus({280, 268}));
    m.add(new Bus({280, 332}));
    m.add(new Lake({168, 220}));
    m.add(new Lake({168, 380}));
    m.add(new Bus({120, 268}));
    m.add(new Bus({120, 332}));

    for (int iterations = 0; iterations < 5000; ++iterations) m.update();

    EXPECT_GT(main_car->get_bbox()->m_center.distance(
                  autonomous_car->get_bbox()->m_center),
              350);
}

TEST(Autonomy, sensor_limitation) {
    // Prepare the map
    MapNoGui m;
    m.init();

    // Add the target Car and an Autonomous vehicle
    auto main_car = new Car({700, 300});
    auto autonomous_car = new AutonomousCar({200, 300}, main_car);
    m.add(main_car);
    m.add(autonomous_car);

    // Add obstacles
    m.add(new Lake({232, 220}));
    m.add(new Lake({232, 380}));
    m.add(new Bus({280, 268}));
    m.add(new Bus({280, 332}));
    m.add(new Lake({232, 540}));
    m.add(new Bus({280, 492}));
    m.add(new Bus({280, 428}));

    for (int iterations = 0; iterations < 5000; ++iterations) m.update();

    EXPECT_GT(main_car->get_bbox()->m_center.distance(
                  autonomous_car->get_bbox()->m_center),
              350);
}

TEST(Autonomy, zigzag) {
    // Prepare the map
    MapNoGui m;
    m.init();

    // Add the target Car and an Autonomous vehicle
    auto main_car = new Car({700, 300});
    auto autonomous_car = new AutonomousCar({200, 300}, main_car);
    m.add(main_car);
    m.add(autonomous_car);

    // Add obstacles
    double pos;
    m.add(new Lake({232, 220}));
    m.add(new Bus({280, 268}));
    m.add(new Bus({280, 332}));
    m.add(new Lake({168, 220}));

    pos = 268;
    for (int i = 0; i < 4; ++i) {
        m.add(new Bus({120, pos}));
        pos += 64;
    }

    pos = 168;
    for (int i = 0; i < 7; ++i) {
        m.add(new Lake({pos, 508}));
        pos += 64;
    }

    m.add(new Lake({328, 348}));
    m.add(new Lake({392, 348}));

    pos = 332;
    for (int i = 0; i < 4; ++i) {
        m.add(new Bus({440, pos}));
        pos -= 64;
    }

    pos = 460;
    for (int i = 0; i < 4; ++i) {
        m.add(new Bus({600, pos}));
        pos -= 64;
    }

    // Calculate how many iterations it takes
    // to reach the target
    int iterations = 0;

    for (; iterations < 1500; ++iterations) {
        m.update();
        if (main_car->get_bbox()->m_center.distance(
                autonomous_car->get_bbox()->m_center) < 30)
            break;
    }

    EXPECT_NEAR(iterations, 680, 20);
}
