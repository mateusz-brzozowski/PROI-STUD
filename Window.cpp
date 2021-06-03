#include "Window.h"

#include <SDL.h>

#include <cassert>
#include <iostream>

static bool is_interesting_key(SDL_Keycode k) {
    return k == SDLK_w || k == SDLK_a || k == SDLK_s || k == SDLK_d;
}

void WindowRenderer::before_render() { SDL_RenderClear(m_attached_renderer); }

void WindowRenderer::render(IMapObject* object) {
    SDL_RenderCopyEx(m_attached_renderer, object->get_texture(), NULL,
                     object->get_texture_position(),
                     object->get_texture_rotation(), NULL, SDL_FLIP_NONE);
}

void WindowRenderer::after_render() { SDL_RenderPresent(m_attached_renderer); }

Window::~Window() { clean(); }

void Window::init(const char* title, int width, int height, bool fullscreen) {
    // Only permit one initialization
    if (m_is_running) return;

    assert(!m_sdl_window);
    assert(!m_renderer);

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cerr << "SDL Initialized\n";

        // Try to create a Window
        m_sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, width, height,
                                        fullscreen ? SDL_WINDOW_FULLSCREEN : 0);

        if (!m_sdl_window) {
            std::cerr << "Failed to create window: " << SDL_GetError() << '\n';
            return;
        }

        std::cerr << "Window crated\n";
        m_width = width;
        m_height = height;

        // Add a renderer to the new window
        m_renderer = SDL_CreateRenderer(m_sdl_window, -1, 0);

        if (!m_renderer) {
            std::cerr << "Failed to create renderer: " << SDL_GetError()
                      << '\n';
            return;
        }

        std::cerr << "Renderer created\n";
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
        m_is_running = true;
    } else {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << '\n';
    }
}

SDL_Texture* Window::load_texture(const char* file, int* w, int* h) {
    // Load the BMP file
    SDL_Surface* tmp_surf = SDL_LoadBMP(file);
    if (!tmp_surf) {
        std::cerr << "Failed to load BMP: " << SDL_GetError() << '\n';
        m_is_running = false;
        return NULL;
    }

    // Create a texture from that surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, tmp_surf);

    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << '\n';
        m_is_running = false;
    }

    // Set the width and height
    if (w) *w = tmp_surf->w;
    if (h) *h = tmp_surf->h;

    // Deallocate the surface (it's not needed anymore), and
    // return a pointer to that allocated Texture.
    SDL_FreeSurface(tmp_surf);
    return texture;
}

void Window::handleEvents() {
    SDL_Event event{};
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                std::cerr << "Quit event registered\n";
                m_is_running = false;
                break;
            case SDL_KEYDOWN:
                if (is_interesting_key(event.key.keysym.sym))
                    m_pressed_keys.insert(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                auto key_ptr = m_pressed_keys.find(event.key.keysym.sym);
                if (key_ptr != m_pressed_keys.end())
                    m_pressed_keys.erase(key_ptr);
                break;
        }
    }
}

void Window::clean() {
    if (m_renderer) {
        std::cerr << "Destroying renderer\n";
        SDL_DestroyRenderer(m_renderer);
        m_renderer = NULL;
    }

    if (m_sdl_window) {
        std::cerr << "Destroying window\n";
        SDL_DestroyWindow(m_sdl_window);
        m_sdl_window = NULL;
    }

    std::cerr << "Quitting SDL\n";
    SDL_Quit();
}
