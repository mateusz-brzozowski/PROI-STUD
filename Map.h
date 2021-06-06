#pragma once
#include <SDL.h>

#include <memory>
#include <vector>

#include "IMap.h"
#include "IMapObject.h"
#include "IMapView.h"
#include "Window.h"

/**
 * Map is an implementation of the IMap interface
 * with the help of SDL.
 */
class MapWithSDL : public IMap {
   protected:
    /// Window connencted to this map
    Window m_window{};

   public:
    /**
     * Initializes connections with the Window.
     */
    void init() override;

    /**
     * Runs and updates all objects as long as the Window
     * is running.
     */
    void loop() override;

    /**
     * Loads a texture from a file, while also updating
     * provided texture width and height,
     * in the context of the attached window's renderer/
     */
    SDL_Texture* load_texture(char const* file, int* w = nullptr,
                              int* h = nullptr) override;

    /**
     * get_bounds() is a method to get the maximum allowed position
     * of an object
     */
    inline virtual Vector2D const get_bounds() override {
        return {(double)m_window.get_width(), (double)m_window.get_height()};
    };

    /**
     * get_pressed_keys() is a method that is supposed to return a number
     * encoding the information on key presses.
     *
     * See the KEY_* macros for values corresponding to particular keys.
     */
    inline unsigned char const get_pressed_keys() override {
        return m_window.get_pressed_keys();
    }
};
