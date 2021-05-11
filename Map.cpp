#include "Map.h"

#include <SDL.h>

#include <memory>

void Map::draw(IMapObject* object) {
    SDL_RenderCopyEx(m_window.get_renderer(), object->get_texture(), NULL,
                     object->get_texture_position(),
                     object->get_texture_rotation(), NULL, SDL_FLIP_NONE);
}

void Map::init() { m_window.init(); }

void Map::loop() {
    uint32_t frame_time = 1000 / 60;

    while (m_window.is_running()) {
        uint32_t start = SDL_GetTicks();
        m_window.handleEvents();

        update();
        render();

        uint32_t since_start = SDL_GetTicks() - start;
        if (frame_time > since_start) SDL_Delay(frame_time - since_start);
    }
}

void Map::add(std::unique_ptr<IMapObject> object) {
    object->set_map(this);
    m_objects.push_back(std::move(object));
}

void Map::render() {
    SDL_RenderClear(m_window.get_renderer());
    for (auto const& obj : m_objects) draw(obj.get());
    SDL_RenderPresent(m_window.get_renderer());
}

void Map::update() {
    for (auto const& obj : m_objects) obj->update();
}
