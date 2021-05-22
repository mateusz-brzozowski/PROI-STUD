#include "Car.h"

#include <SDL.h>
#include <stdlib.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <math.h> 

#include "Tools.h"
#include "Window.h"

void Car::set_map(Map* map) { m_map = map; }

Car::Car(const bool userCar, const Vector2D& start_positon, Car* follow_car)
    : userCar_(userCar), m_position(start_positon), follow_car_(follow_car)
{}

void Car::update() {
    if (!userCar_) {
         //First, update the angle
         m_angle += m_map->get_window().is_pressed(SDLK_d) ? .1 : 0.0;
         m_angle -= m_map->get_window().is_pressed(SDLK_a) ? .1 : 0.0;

         //Then move the car in the direction pointed by angle
         double distance =
             (m_map->get_window().is_pressed(SDLK_w) ? 5.0 : 0.0) -
             (m_map->get_window().is_pressed(SDLK_s) ? 5.0 : 0.0);

         Vector2D move_vec = rotate_vector({distance, 0}, m_angle);

         m_position.x = m_position.x + move_vec.x;
         m_position.y = m_position.y + move_vec.y;
    } 
    else {
        if (distance(follow_car_->m_position, m_position) > 20) {
            Vector2D direction = follow_car_->m_position - m_position;
            float angle = atan2(direction.y, direction.x);
            direction.normalize();

            m_angle = angle;
            m_position = m_position + (direction * (move_speed * 1/60));
        }
    }
    
    // Clamp the values
    double w = m_map->get_window().get_width() - 18;
    double h = m_map->get_window().get_height() - 18;

    m_position.x = CLAMP(m_position.x, 0, w);
    m_position.y = CLAMP(m_position.y, 0, h);

    // Update the texture position
    m_texture_position.x = (int)m_position.x;
    m_texture_position.y = (int)m_position.y;
    
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
