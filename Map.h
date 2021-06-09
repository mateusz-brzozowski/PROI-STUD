#pragma once
#include <SDL.h>

#include <memory>
#include <vector>

#include "IMap.h"
#include "IMapObject.h"
#include "IMapView.h"
#include "Tools.h"
#include "Window.h"

/**
 * MapWithSDL is an implementation of the IMap interface
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
    SDL_Texture* load_texture(char const* file, float* w = nullptr,
                              float* h = nullptr) override;

    /**
     * get_bounds() is a method to get the maximum allowed position
     * of an object
     */
    Vector2D const get_bounds() override {
        return {(double)m_window.get_width(), (double)m_window.get_height()};
    };

    /**
     * get_pressed_keys() is a method that is supposed to return a number
     * encoding the information on key presses.
     *
     * See the KEY_* macros for values corresponding to particular keys.
     */
    unsigned char const get_pressed_keys() override {
        return m_window.get_pressed_keys();
    }

    /**
     * get_window() is a special method,
     * to get the underlaying Window class.
     */
    Window const& get_window() { return m_window; }
};

/**
 * MapNoGUI is a special implementation of the IMap interface
 * that is not attached to any GUI/drawing system.
 *
 * This class is used to allow automated tests of objects
 * that need to be attached to some map.
 */
class MapNoGui : public IMap {
   private:
    unsigned char m_pressed_keys{0};
    unsigned m_max_iterations{1000000};

   public:
    MapNoGui(int max_iterations = -1) : m_max_iterations(max_iterations) {}
    void loop() override;
    SDL_Texture* load_texture(char const* file, float* w = nullptr,
                              float* h = nullptr) override;
    Vector2D const get_bounds() override { return {800, 600}; }
    unsigned char const get_pressed_keys() { return m_pressed_keys; }
    void set_pressed_keys(unsigned char mask) { m_pressed_keys = mask; }
};
