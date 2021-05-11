#include <SDL.h>

#include "Map.h"

#include <memory>

Map::Map(const Window& window) : m_window(window) {}

void Map::draw(IMapObject* object) {
    SDL_RenderCopyEx(m_window.get_renderer(), object->get_texture(), NULL,
                     object->get_texture_position(),
                     object->get_texture_rotation(), NULL, SDL_FLIP_NONE);
}

void Map::init() {
    // TODO
}

void Map::add(std::unique_ptr<IMapObject> object) {
    object->set_map(*this);
    m_objects.push_back(std::move(object));
}

void Map::render() {
    SDL_RenderClear(m_window.get_renderer());
    for (auto const & obj : m_objects) draw(obj.get());
    SDL_RenderPresent(m_window.get_renderer());
}

void Map::update() {
    for (auto const & obj : m_objects) obj->update();
}
