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

void Car::clamp_position() {
    // Clamp the values
    double w = m_map->get_window().get_width() - 18;
    double h = m_map->get_window().get_height() - 18;

    m_position.x = CLAMP(m_position.x, 0, w);
    m_position.y = CLAMP(m_position.y, 0, h);

    // Update the texture position
    m_texture_position.x = (int)m_position.x;
    m_texture_position.y = (int)m_position.y;
}

void Car::update() {
    // First, update the angle
    m_angle += m_map->get_window().is_pressed(SDLK_d) ? .1 : 0.0;
    m_angle -= m_map->get_window().is_pressed(SDLK_a) ? .1 : 0.0;

    // Then move the car in the direction pointed by angle
    double distance = (m_map->get_window().is_pressed(SDLK_w) ? 5.0 : 0.0) -
                      (m_map->get_window().is_pressed(SDLK_s) ? 5.0 : 0.0);

    m_position += rotate_vector({distance, 0}, m_angle);

    clamp_position();
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
    if (distance(m_follow_car->get_position(), m_position) > 20) {
        Vector2D direction = m_follow_car->get_position() - m_position;
        float angle = atan2(direction.y, direction.x);
        direction.normalize();

        m_angle = angle;
        m_position += (direction * (m_speed * 1 / 60));
        clamp_position();
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
