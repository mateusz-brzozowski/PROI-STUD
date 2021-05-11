#include "Map.h"

Map::Map(const Window& window_) : window(window_) {}

Map::~Map() {}

void Map::draw(const std::unique_ptr<IMapObject>& object) {
    SDL_RenderCopyEx(window.get_renderer(), object->get_texture(), NULL,
                     object->get_texture_position(),
                     object->get_texture_rotation(), NULL, SDL_FLIP_NONE);
}

void Map::init() {
    // TO DO
}

void Map::add(std::unique_ptr<IMapObject>& object) {
    map.push_back(std::move(object));
}

void Map::render() {
    SDL_RenderClear(window.get_renderer());
    for (int i = 0; i < map.size(); i++) {
        draw(map[i]);
    }
    SDL_RenderPresent(window.get_renderer());
}

void Map::update() {
    for (int i = 0; i < map.size(); i++) {
        map[i]->update();
    }
}
