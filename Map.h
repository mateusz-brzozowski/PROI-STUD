#pragma once
#include <SDL.h>

#include <memory>
#include <vector>

#include "IMapObject.h"
#include "Window.h"

/**
 * Map is a central object that manages every object on given map
 * and handles connections to objects that view the map and can provide
 * some events back to the map.
 */
class Map {
   private:
    /// Vector of elements on this map
    std::vector<std::unique_ptr<IMapObject>> m_objects;

    /// Window connencted to this map
    Window m_window{};

    /**
     * Renders an object on the attached window
     */
    void draw(IMapObject* object);

   public:
    /**
     * Adds an object to the map and assumes ownership of that object.
     */
    void add(std::unique_ptr<IMapObject> object);

    /**
     * Initializes connections with all windows.
     */
    void init();

    /**
     * Runs and updates all objects as long as the main Window
     * is running.
     */
    void loop();

    /**
     * Updates all objects
     */
    void update();

    /**
     * Renders all objects
     */
    void render();

    /**
     * Returns a reference to the attached Window
     */
    inline Window& get_window() { return m_window; }
};
