#pragma once
#include <SDL.h>

class Window {
   private:
    SDL_Window* m_sdl_window{NULL};
    SDL_Renderer* m_renderer{NULL};
    int m_width{-1};
    int m_height{-1};
    bool m_is_running{false};

   public:
    ~Window();
    void init(const char* title = "PROI Auto", int width = 800,
              int height = 600, bool fullscreen = false);

    SDL_Texture* load_texture(const char* file);
    void handleEvents();
    void clean();

    inline SDL_Renderer* get_renderer() { return m_renderer; }
    inline int get_width() { return m_width; }
    inline int get_height() { return m_height; }
    inline bool is_running() { return m_is_running; }
};
