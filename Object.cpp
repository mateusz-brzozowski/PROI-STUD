#include "Object.h"

#include <SDL.h>
#include <stdlib.h>

#include "Window.h"

void Object::set_map(IMap* map) { m_map = map; }

void Object::update() {}

SDL_Texture* Object::get_texture() {
    if (!m_texture && m_map) {
        // Load the texture, and its width and height
        m_texture = m_map->load_texture(m_texture_file, &m_texture_position.w,
                                        &m_texture_position.h);

        // Save the width and heigh in `m_position`
        m_position.m_width_half = (double)m_texture_position.w * .5;
        m_position.m_height_half = (double)m_texture_position.h * .5;

        // Save texture position
        m_position.update_sdl_rect_position(&m_texture_position);
    }

    return m_texture;
}
