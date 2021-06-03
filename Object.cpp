#include "Object.h"

#include <SDL.h>
#include <stdlib.h>

#include "Window.h"

void Object::set_map(Map* map) { m_map = map; }

void Object::update() {}

SDL_Texture* Object::get_texture() {
    if (!m_texture && m_map)
        m_texture = m_map->get_window().load_texture(
            m_texture_file, &m_texture_position.w, &m_texture_position.h);

    return m_texture;
}

SDL_Rect* Object::get_texture_position() { return &m_texture_position; }

double Object::get_texture_rotation() { return m_angle; }
