#include "Map.h"

#include <SDL.h>

#include <memory>

void Map::init() {
    m_window.init();
    add_view(std::move(m_window.create_mapview()));
}

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
    for (auto const& view : m_views) {
        view->before_render();
        for (auto const& obj : m_objects) view->render(obj.get());
        view->after_render();
    }
}

void Map::update() {
    for (auto const& obj : m_objects) obj->update();
}
