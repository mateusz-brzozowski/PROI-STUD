#include "Car.h"

#include <SDL.h>
#include <math.h>
#include <stdlib.h>

#include <algorithm>
#include <cmath>
#include <iostream>

#include "Tools.h"
#include "Window.h"

void Car::set_map(Map* map) { m_map = map; }

bool Car::validate_new_position(Vector2D temp_pos) {
    // Clamp within Map bounds
    double w = m_map->get_window().get_width() - 9;
    double h = m_map->get_window().get_height() - 9;

    temp_pos.x = CLAMP(temp_pos.x, 9, w);
    temp_pos.y = CLAMP(temp_pos.y, 9, h);

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
    m_position.m_angle += m_map->get_window().is_pressed(SDLK_d) ? .1 : 0.0;
    m_position.m_angle -= m_map->get_window().is_pressed(SDLK_a) ? .1 : 0.0;

    // Then move the car in the direction pointed by angle
    double distance = (m_map->get_window().is_pressed(SDLK_w) ? 5.0 : 0.0) -
                      (m_map->get_window().is_pressed(SDLK_s) ? 5.0 : 0.0);

    validate_new_position(m_position.m_center +
                          Vector2D{distance, 0}.rotate(m_position.m_angle));
}

SDL_Texture* Car::get_texture() {
    if (!m_texture && m_map) {
        // Load the texture, and its width and height
        m_texture = m_map->get_window().load_texture(
            m_texture_file, &m_texture_position.w, &m_texture_position.h);

        // Save the width and heigh in `m_position`
        m_position.m_width_half = (double)m_texture_position.w * .5;
        m_position.m_height_half = (double)m_texture_position.h * .5;

        // Save texture position
        m_position.update_sdl_rect_position(&m_texture_position);
    }

    return m_texture;
}

void AutonomousCar::update() {
    Vector2D& target_pos = m_target->get_bbox()->m_center;

    if (target_pos.distance(m_position.m_center) > 30) {
        Vector2D direction = target_pos - m_position.m_center;
        m_position.m_angle = atan2(direction.y, direction.x);
        direction.normalize();
        validate_new_position(m_position.m_center +
                              (direction * (m_speed * 1 / 60)));
    }
}

SDL_Texture* AutonomousCar::get_texture() {
    if (!m_texture && m_map) {
        // Load the texture, and its width and height
        m_texture = m_map->get_window().load_texture(
            m_texture_file, &m_texture_position.w, &m_texture_position.h);

        // Save the width and heigh in `m_position`
        m_position.m_width_half = (double)m_texture_position.w * .5;
        m_position.m_height_half = (double)m_texture_position.h * .5;

        // Save texture position
        m_position.update_sdl_rect_position(&m_texture_position);
    }

    return m_texture;
}
