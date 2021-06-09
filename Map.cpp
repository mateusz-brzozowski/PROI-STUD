#include "Map.h"

#include <SDL.h>

#include <cstring>
#include <memory>

void MapWithSDL::init() {
    m_window.init();
    add_view(std::move(m_window.get_renderer()));
}

void MapWithSDL::loop() {
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

SDL_Texture* MapWithSDL::load_texture(char const* file, int* w, int* h) {
    return m_window.load_texture(file, w, h);
}

void MapNoGui::loop() {
    for (unsigned i = m_max_iterations; i != 0; i--) {
        update();
        render();
    }
}

SDL_Texture* MapNoGui::load_texture(char const* file, int* w, int* h) {
    int width = 32;
    int height = 32;

    if (!std::strcmp(file, "images/car.bmp")) {
        width = 18;
        height = 18;
    } else if (!std::strcmp(file, "images/car2.bmp")) {
        width = 18;
        height = 18;
    } else if (!std::strcmp(file, "images/bus.bmp")) {
        height = 64;
    } else if (!std::strcmp(file, "images/lake.bmp")) {
        width = 64;
    }

    if (w) *w = width;
    if (h) *h = height;

    return nullptr;
}
