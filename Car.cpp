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

bool Car::validate_new_position(Vector2D new_pos) {
    // Clamp within Map bounds
    double w = m_map->get_window().get_width() - 18;
    double h = m_map->get_window().get_height() - 18;

    new_pos.x = CLAMP(new_pos.x, 0, w);
    new_pos.y = CLAMP(new_pos.y, 0, h);

    // Check for collisions
    SDL_Rect new_texture_pos = m_texture_position;
    new_texture_pos.x = new_pos.x;
    new_texture_pos.y = new_pos.y;

    for (auto& e : m_map->get_objects())
        if (*e != *this &&
            CollisionAABB(e->get_texture_position(), &new_texture_pos)) {
            // Collision with a different object detected
            // - don't update the position
            return false;
        }

    m_position = new_pos;
    m_texture_position = new_texture_pos;
    return true;
}

void Car::update() {
    // First, update the angle
    m_angle += m_map->get_window().is_pressed(SDLK_d) ? .1 : 0.0;
    m_angle -= m_map->get_window().is_pressed(SDLK_a) ? .1 : 0.0;

    // Then move the car in the direction pointed by angle
    double distance = (m_map->get_window().is_pressed(SDLK_w) ? 5.0 : 0.0) -
                      (m_map->get_window().is_pressed(SDLK_s) ? 5.0 : 0.0);

    validate_new_position(m_position + Vector2D{distance, 0}.rotate(m_angle));
}

SDL_Texture* Car::get_texture() {
    if (!m_texture && m_map) {
        m_texture = m_map->get_window().load_texture("images/car.bmp");
        m_texture_position.h = 18;
        m_texture_position.w = 18;
    }

    return m_texture;
}

SDL_Rect* Car::get_texture_position() { return &m_texture_position; }

double Car::get_texture_rotation() { return m_angle * 180.0 / M_PI; }

void AutonomousCar::update() {
    if (m_follow_car->get_position().distance(m_position) > 30) {
        Vector2D direction = m_follow_car->get_position() - m_position;
        m_angle = atan2(direction.y, direction.x);
        direction.normalize();
        validate_new_position(m_position + (direction * (m_speed * 1 / 60)));
    }
}

SDL_Texture* AutonomousCar::get_texture() {
    if (!m_texture && m_map) {
        m_texture = m_map->get_window().load_texture("images/car2.bmp");
        m_texture_position.h = 18;
        m_texture_position.w = 18;
    }

    return m_texture;
}
