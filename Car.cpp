#include "Car.h"

#include <SDL.h>
#include <math.h>
#include <stdlib.h>

#include <algorithm>
#include <cmath>
#include <iostream>

#include "Car.h"
#include "IMap.h"
#include "Tools.h"

void Car::set_map(IMap* map) {
    m_map = map;

    // Load the texture, and its width and height
    m_texture = m_map->load_texture(m_texture_file, &m_texture_position.w,
                                    &m_texture_position.h);

    // Save the width and heigh in `m_position`
    m_position.m_width_half = (double)m_texture_position.w * .5;
    m_position.m_height_half = (double)m_texture_position.h * .5;

    // Save texture position
    m_position.update_sdl_rect_position(&m_texture_position);
}

bool Car::validate_new_position(Vector2D temp_pos) {
    // Clamp within Map bounds
    Vector2D bounds = m_map->get_bounds() - Vector2D{9, 9};

    temp_pos.x = CLAMP(temp_pos.x, 9, bounds.x);
    temp_pos.y = CLAMP(temp_pos.y, 9, bounds.y);

    std::swap(m_position.m_center, temp_pos);

    // Check for collisions
    for (auto& o : m_map->get_objects())
        if (*o != *this && m_position.collides(*o->get_bbox())) {
            // Collision with a different object detected
            // - swap back the previous position
            std::swap(m_position.m_center, temp_pos);
            return false;
        }

    m_position.update_sdl_rect_position(&m_texture_position);
    return true;
}

void Car::update() {
    // First, update the angle
    auto pressed_keys = m_map->get_pressed_keys();
    m_position.m_angle += pressed_keys & KEY_D ? .1 : 0.0;
    m_position.m_angle -= pressed_keys & KEY_A ? .1 : 0.0;

    // Then move the car in the direction pointed by angle
    double distance =
        (pressed_keys & KEY_W ? 5.0 : 0.0) - (pressed_keys & KEY_S ? 5.0 : 0.0);

    validate_new_position(m_position.m_center +
                          Vector2D{distance, 0}.rotate(m_position.m_angle));
}

RotatedRect* AutonomousCar::sensor_collides(Sensor& sensor) {
    for (auto& o : m_map->get_objects())
        if (o.get() != m_target && o.get() != this &&
            sensor.bbox.collides(*o->get_bbox()))
            return o->get_bbox();
    return nullptr;
}

void AutonomousCar::update_sensor_pos() {
    for (auto& s : m_sensors) {
        s.bbox.m_center =
            m_position.m_center + s.center_offset.rotated(m_position.m_angle);
        s.bbox.m_angle = m_position.m_angle + s.angle_offset;
    }
}

void AutonomousCar::update() {
    update_sensor_pos();

    // Detect collisions
    double avoid_factor = 0;

    for (auto& sensor : m_sensors) {
        if (sensor_collides(sensor)) {
            avoid_factor += sensor.avoid_factor;
        }
    }

    // Move
    Vector2D new_pos = m_position.m_center;
    new_pos.y += sin(m_position.m_angle) * m_speed;
    new_pos.x += cos(m_position.m_angle) * m_speed;

    // Rotate wheels
    if (avoid_factor) {
        m_position.m_angle += M_PI / 36 * avoid_factor;
    } else {
        Vector2D target_pos = m_target->get_bbox()->m_center;

        if (target_pos.distance(m_position.m_center) < 30) return;

        Vector2D direction = target_pos - m_position.m_center;
        double angle_to_target =
            m_position.m_angle - atan2(direction.y, direction.x);
        m_position.m_angle +=
            m_speed * (std::sin(angle_to_target) < 0 ? .03 : -.03);
    }

    validate_new_position(new_pos);
}

void AutonomousCar::set_map(IMap* map) {
    m_map = map;

    // Load the texture, and its width and height
    m_texture = m_map->load_texture(m_texture_file, &m_texture_position.w,
                                    &m_texture_position.h);

    // Save the width and heigh in `m_position`
    m_position.m_width_half = (double)m_texture_position.w * .5;
    m_position.m_height_half = (double)m_texture_position.h * .5;

    // Save texture position
    m_position.update_sdl_rect_position(&m_texture_position);

    initialize_sensors();
}

void AutonomousCar::render_on(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    for (auto const& sensor : m_sensors) {
        auto sensor_pts = sensor.bbox.vertices();
        SDL_FPoint pts[5];

        for (int i = 0; i < 5; ++i)
            pts[i] = {
                (float)sensor_pts.at(i % 4).x,
                (float)sensor_pts.at(i % 4).y,
            };

        SDL_RenderDrawLinesF(renderer, pts, 5);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void AutonomousCar::initialize_sensors() { 
    m_sensors.reserve(5);
    double front_offset = sensor_lenght_half + m_position.m_width_half;
    double angle_offset = sensor_lenght_half * M_SQRT1_2;
    // Front sensor
    m_sensors.emplace_back(Vector2D{front_offset, 0}, 0, 1);
    // Right-Front sensor
    m_sensors.emplace_back(Vector2D{front_offset, m_position.m_height_half}, 0,
                           -1);
    // Right-Corner sensor
    m_sensors.emplace_back(Vector2D{angle_offset + m_position.m_width_half,
                                    angle_offset + m_position.m_height_half},
                           M_PI_4, -.5);
    // Left-Front Sensor
    m_sensors.emplace_back(Vector2D{front_offset, -m_position.m_height_half}, 0,
                           1);
    // Left-Corner sensor
    m_sensors.emplace_back(Vector2D{angle_offset + m_position.m_width_half,
                                    -(angle_offset + m_position.m_height_half)},
                           -M_PI_4, .5);
}