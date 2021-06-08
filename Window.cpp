#include "Window.h"

#include <SDL.h>

#include <cassert>
#include <iostream>

#include "IMap.h"

static unsigned char convert_keycode(SDL_Keycode k) {
    switch (k) {
        case SDLK_w:
            return KEY_W;
        case SDLK_a:
            return KEY_A;
        case SDLK_s:
            return KEY_S;
        case SDLK_d:
            return KEY_D;
        case SDLK_SPACE:
            return KEY_Space;
    }
    return 0;
}

bool WindowRenderer::init(SDL_Window* window) {
    m_sdl_renderer = SDL_CreateRenderer(window, -1, 0);
    if (!m_sdl_renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << '\n';
        return false;
    }

    std::cerr << "Renderer created\n";
    SDL_SetRenderDrawColor(m_sdl_renderer, 255, 255, 255, 255);
    return true;
}

void WindowRenderer::before_render() { SDL_RenderClear(m_sdl_renderer); }

void WindowRenderer::render(IMapObject* object) {
    SDL_RenderCopyEx(m_sdl_renderer, object->get_texture(), NULL,
                     object->get_texture_position(),
                     object->get_texture_rotation(), NULL, SDL_FLIP_NONE);
}

void WindowRenderer::after_render() {
    for (auto const& addon : m_addons) addon->render_on(m_sdl_renderer);
    SDL_RenderPresent(m_sdl_renderer);
}

void WindowRenderer::clean() {
    if (m_sdl_renderer) {
        std::cerr << "Destroying renderer\n";
        SDL_DestroyRenderer(m_sdl_renderer);
        m_sdl_renderer = nullptr;
    }
}

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
        m_renderer.reset(new WindowRenderer);

        // Initialize the renderer - and only if it succeeds we can say
        // the loop is actually running
        if (m_renderer->init(m_sdl_window)) {
            m_is_running = true;
        }

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
    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(m_renderer->get_renderer(), tmp_surf);

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
                m_pressed_keys |= convert_keycode(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                m_pressed_keys &= ~convert_keycode(event.key.keysym.sym);
                break;
        }
    }
}

void Window::clean() {
    if (m_renderer) m_renderer->clean();

    if (m_sdl_window) {
        std::cerr << "Destroying window\n";
        SDL_DestroyWindow(m_sdl_window);
        m_sdl_window = NULL;
    }

    std::cerr << "Quitting SDL\n";
    SDL_Quit();
}
