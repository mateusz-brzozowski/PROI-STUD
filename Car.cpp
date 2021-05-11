#include "Car.h"

#include <SDL.h>
#include <stdlib.h>

#include "Window.h"

void Car::set_map(Map* map) { m_map = map; }

void Car::update() {
    m_position.x = ++m_count % m_map->get_window().get_width();
    m_angle = m_count;
}

SDL_Texture* Car::get_texture() {
    if (!m_texture && m_map) {
        m_texture = m_map->get_window().load_texture("images/car.bmp");
        m_position.h = 18;
        m_position.w = 18;
    }

    return m_texture;
}

SDL_Rect* Car::get_texture_position() { return &m_position; }

double Car::get_texture_rotation() { return m_angle; }
